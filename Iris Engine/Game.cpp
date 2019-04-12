#include "Game.h"
#include "Config.h"
#include "Locator.h"
#include "MessageBoxLogger.h"
#include "MixAudio.h"
#include "TextWindow.h"
#include "ButtonMenu.h"
#include "BackgroundObject.h"
#include "LRUCache.h"
#include "IClickableObject.h"
#include "SDLRenderer.h"
#include "GPURenderer.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

bool Game::instantiated = false;

Game::Game()
	:CONFIG_FILE_PATH("config.lua")
{
	// Ensure there is only one instance of this class
	assert(!instantiated);
	instantiated = true;
}

Game::~Game()
{
}

void Game::start()
{
	// Initialize logging service
	MessageBoxLogger msgBoxLogger;
	Locator::provide(&msgBoxLogger);

	// Initialize input service
	Locator::provide(&gameInput);

	// Initialize audio service
	MixAudio mixAudio(AUDIO_CHANNELS);
	Locator::provide(&mixAudio);

	ILogger* logger = Locator::getLogger();

	// Check if the game is already started
	if (gameState != UNINITIALIZED)
	{
		logger->log(LogCategory::SYSTEM, LogPriority::ERROR, u8"The game can't be started twice.");
		return;
	}

	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO))
	{
		logger->log(LogCategory::SYSTEM, LogPriority::ERROR, u8"Unable to initialize SDL:\n" + std::string(SDL_GetError()));
		return;
	}

	int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	if (IMG_Init(imgFlags) != imgFlags)
	{
		logger->log(LogCategory::SYSTEM, LogPriority::ERROR, u8"Unable to initialize SDL_Image:\n" + std::string(IMG_GetError()));
		return;
	}

	if (TTF_Init())
	{
		logger->log(LogCategory::SYSTEM, LogPriority::ERROR, u8"Unable to initialize SDL_ttf:\n" + std::string(TTF_GetError()));
		return;
	}

	int mixerFlags = MIX_INIT_OGG | MIX_INIT_FLAC;
	if (Mix_Init(mixerFlags) != mixerFlags)
	{
		logger->log(LogCategory::SYSTEM, LogPriority::ERROR, u8"Unable to initialize SDL_mixer:\n" + std::string(Mix_GetError()));
		return;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024))
	{
		logger->log(LogCategory::AUDIO, LogPriority::ERROR, u8"Unable to open audio device:\n" + std::string(Mix_GetError()));
		return;
	}
	Mix_AllocateChannels(AUDIO_CHANNELS);

	// Load config
	if (Config::load(CONFIG_FILE_PATH))
	{
		// Create main window
		createMainWindow();

		if (mainWindow)
		{
			// Set the icon of the window
			SDL_Surface* icon = IMG_Load(Config::values().game.iconFile.c_str());

			if (icon)
			{
				SDL_SetWindowIcon(mainWindow, icon);
				SDL_FreeSurface(icon);
			}
			else
			{
				logger->log(LogCategory::SYSTEM, LogPriority::ERROR, u8"Window icon could not be loaded:\n" + std::string(IMG_GetError()));
			}

			// Create renderer and start the game
			renderer = new GPURenderer(mainWindow);

			if (renderer->isValid())
			{
				// Set the game to fullscreen if necessary
				if (Config::values().screen.fullscreen)
					toggleFullscreen();
				else
					gameInput.correctMouseForWindowScaling(renderer->getScalingFactor(), renderer->getLetterboxingOffset());

				// Create cache service
				LRUCache lruCache(renderer);
				Locator::provide(&lruCache);

				startGame();

				// Game is exiting, free resources.
				delete renderer;
			}
			else
			{
				logger->log(LogCategory::SYSTEM, LogPriority::ERROR, u8"Could not create renderer:\n" + std::string(SDL_GetError()));
			}

			// Destroy window
			SDL_DestroyWindow(mainWindow);
		}
		else
		{
			logger->log(LogCategory::SYSTEM, LogPriority::ERROR, u8"Could not create window:\n" + std::string(SDL_GetError()));
		}
	}
}

inline bool Game::isExiting()
{
	return gameState == EXITING;
}

void Game::toggleFullscreen()
{
	Vector2<int> res(Config::values().screen.resolution.x, Config::values().screen.resolution.y);

	renderer->setFullScreen(!renderer->getFullscreen());
	gameInput.correctMouseForWindowScaling(renderer->getScalingFactor(), renderer->getLetterboxingOffset());
}

void Game::createMainWindow()
{
	// Get screen size
	SDL_Rect display;

	if (SDL_GetDisplayBounds(0, &display) == 0)
	{
		int desiredW = Config::values().screen.resolution.x;
		int desiredH = Config::values().screen.resolution.y;

		// If the game window doesn't fit the screen, scale it
		display.w *= 0.9f;
		display.h *= 0.9f;

		if (desiredW > display.w || desiredH > display.h)
		{
			float ratioWindow = (float)desiredW / desiredH;
			float ratioScreen = (float)display.w / display.h;

			float scalingFactor = (ratioScreen < ratioWindow) ? (float)display.w / desiredW : (float)display.h / desiredH;

			desiredW *= scalingFactor;
			desiredH *= scalingFactor;
		}

		int windowFlags = SDL_WINDOW_OPENGL;

		mainWindow = SDL_CreateWindow(
			Config::values().game.name.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			desiredW,
			desiredH,
			windowFlags
		);
	}
}

void Game::startGame()
{
	gameState = PLAYING;

	textWindow = new TextWindow(renderer);
	choicesMenu = new ButtonMenu(
		renderer,
		Config::values().choices.background,
		Config::values().zindexes.choices,
		Config::values().choices.position,
		Config::values().choices.size,
		Config::values().choices.separation,
		Config::values().choices.useVerticalLayout
	);
	background = new BackgroundObject(Config::values().zindexes.backgrounds);
	sceneTransition = new BackgroundObject(Config::values().zindexes.sceneTransitionEffects);
	
	gameObjectManager.add(textWindow);
	gameObjectManager.add(choicesMenu);
	gameObjectManager.add(background);
	gameObjectManager.add(sceneTransition);

	gameObjectManager.calculateMinimumElapsedTime();

	// Set up lua environment and run first script
	luaEnvironment.setUp(renderer, textWindow, &gameObjectManager, choicesMenu, background, sceneTransition);

	if (luaEnvironment.ready())
		luaEnvironment.resume();

	// Main loop
	while (!isExiting())
	{
		gameLoop();
	}
}

void Game::gameLoop()
{
	SDL_Event currentEvent;

	switch (gameState)
	{
	case PLAYING:
		// Resume Lua execution
		if (luaEnvironment.ready())
			luaEnvironment.resume();

		if (luaEnvironment.shouldExitGame())
			gameState = EXITING;

		// Fire right mouse button event if necessary
		// We do this here so that if multiple events are fired
		// in the same frame, this one is the first to be pushed
		// into the stack and the last one to be executed
		gameInput.handleRightMouseEvent();

		// Update objects
		gameObjectManager.updateAll();
		
		IClickableObject* object = gameInput.getObjectPointedByUser();
		if (object)
			object->handleMouseInput();

		// Render
		renderer->clear();
		gameObjectManager.drawAll(renderer);
		renderer->present();

		// Consume input
		gameInput.consume();

		// Handle events
		while (SDL_PollEvent(&currentEvent))
		{
			if (currentEvent.type == SDL_QUIT)
			{
				gameState = EXITING;
			}
			else if (currentEvent.type == SDL_MOUSEBUTTONDOWN || currentEvent.type == SDL_MOUSEBUTTONUP)
			{
				gameInput.updateMouseButton(currentEvent.button.button, currentEvent.type == SDL_MOUSEBUTTONDOWN);
			}
			else if (currentEvent.type == SDL_MOUSEWHEEL)
			{
				gameInput.updateMouseWheel(currentEvent.wheel.y, currentEvent.wheel.direction);
			}
			else if ((currentEvent.type == SDL_KEYDOWN || currentEvent.type == SDL_KEYUP))
			{
				if (currentEvent.key.keysym.scancode == SDL_SCANCODE_RETURN || currentEvent.key.keysym.scancode == SDL_SCANCODE_KP_ENTER)
					gameInput.updateEnterKey(currentEvent.type == SDL_KEYDOWN);
			}
		}

		// Toggle fullscreen
		if (gameInput.actionToggleFullscreen())
			toggleFullscreen();
	}
}
