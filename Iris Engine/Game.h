#pragma once

#include "GameInput.h"
#include "GameObjectManager.h"
#include "LuaEnvironment.h"
#include <string>

/// <summary>
/// Main class of the engine.
/// Initializes and executes the game loop.
/// </summary>
class Game
{
public:
	Game();
	~Game();
	
	/// <summary>
	/// Initializes and starts the game.
	/// </summary>
	void start();

private:
	enum GameState
	{
		UNINITIALIZED,
		PLAYING,
		EXITING
	};

	// Single instance
	static bool instantiated;

	struct SDL_Window* mainWindow;
	class IRenderer* renderer;

	GameObjectManager gameObjectManager;

	class TextWindow* textWindow;
	class ButtonMenu* choicesMenu;
	class BackgroundObject* background;
	class BackgroundObject* sceneTransition;
	class LuaEnvironment luaEnvironment;

	GameState gameState;
	GameInput gameInput;

	const std::string CONFIG_FILE_PATH;
	const int AUDIO_CHANNELS = 16;

	// Functions	
	bool inline isExiting();
	void toggleFullscreen();
	void createMainWindow();

	// Game control	
	void startGame();
	void gameLoop();
};