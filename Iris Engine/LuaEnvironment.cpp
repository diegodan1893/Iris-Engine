#include "LuaEnvironment.h"
#include "WaitForText.h"
#include "WaitForTransition.h"
#include "WaitForTimer.h"
#include "WaitForFunction.h"
#include "ClearScene.h"
#include "Config.h"
#include "GameObjectManager.h"
#include "TextWindow.h"
#include "BackgroundObject.h"
#include "SpriteObject.h"
#include "ButtonObject.h"
#include "TextObject.h"
#include "Locator.h"
#include "TransitionUtils.h"
#include "InterpolatorType.h"
#include "Cursor.h"
#include "IRenderer.h"

bool LuaEnvironment::instantiated = false;
LuaEnvironment* LuaEnvironment::thisEnvironment;
class IRenderer* LuaEnvironment::renderer;
class GameObjectManager* LuaEnvironment::gameObjectManager;
TextWindow* LuaEnvironment::textWindow;
ButtonMenu* LuaEnvironment::choicesMenu;
BackgroundObject* LuaEnvironment::background;
BackgroundObject* LuaEnvironment::sceneTransitionEffect;

LuaEnvironment::LuaEnvironment()
	:wantsToExit(false)
{
	// Ensure there is only one instance of this class
	assert(!instantiated);
	instantiated = true;
	thisEnvironment = this;
}

void LuaEnvironment::setUp(
	class IRenderer* renderer,
	TextWindow* textWindow,
	GameObjectManager* gameObjectManager,
	class ButtonMenu* choicesMenu,
	BackgroundObject* background,
	BackgroundObject* sceneTransition
)
{
	// Set variables
	this->renderer = renderer;
	this->textWindow = textWindow;
	this->choicesMenu = choicesMenu;
	this->gameObjectManager = gameObjectManager;
	this->background = background;
	this->sceneTransitionEffect = sceneTransition;

	now = last = SDL_GetPerformanceCounter();

	// Set up lua environment
	lua.open_libraries(sol::lib::base, sol::lib::string, sol::lib::math, sol::lib::table, sol::lib::io);

	// Set the random seed to the current time
	lua["math"]["randomseed"](time(0));

	// Register Character class
	lua.new_usertype<LuaCharacter>("Character",
		// Constructor
		"new", sol::factories(&LuaEnvironment::createCharacter),

		// Properties
		"name", sol::property(&LuaCharacter::getName, &LuaCharacter::setName),

		// Functions
		sol::meta_function::call, sol::overload(
			&LuaCharacter::say,
			&LuaCharacter::sayNumber
		)
	);

	// Register Question class
	lua.new_usertype<LuaQuestion>("Question",
		// Constructor
		"new", sol::factories(&LuaEnvironment::createQuestion),

		// Properties
		"answer", sol::property(&LuaQuestion::getAnswer),
		"removeAfterSelection", sol::property(&LuaQuestion::getRemoveAfterSelection, &LuaQuestion::setRemoveAfterSelection),
		"count", sol::property(&LuaQuestion::count),

		// Functions
		"ask", &LuaQuestion::ask
	);

	// Register Object class
	lua.new_usertype<LuaObject>("Sprite",
		// Constructor

		// Properties
		"visible", sol::property(&LuaObject::getVisible),

		// Functions
		"show", sol::overload(
			&LuaObject::show,
			&LuaObject::showTransition
		),
		"hide", sol::overload(
			&LuaObject::hide,
			&LuaObject::hideTransition
		),
		"skipTransition", &LuaObject::skipTransition,
		"setPosition", &LuaObject::setPosition,
		"getPosition", &LuaObject::getPosition,
		"setOrigin", &LuaObject::setOrigin,
		"move", sol::overload(
			&LuaObject::moveInterpolator,
			&LuaObject::move
		)
	);

	// Register Sprite class
	lua.new_usertype<LuaSprite>("Sprite",
		// Constructor
		"new", sol::factories(&LuaEnvironment::createSpriteSimple),

		// Properties

		// Functions
		"defineSpriteSheet", &LuaSprite::defineSpriteSheet,
		"setFrame", &LuaSprite::setFrame,

		// Base class
		sol::base_classes, sol::bases<LuaObject>()
	);

	// Register Button class
	lua.new_usertype<LuaButton>("Button",
		// Constructor
		"new", sol::factories(
			&LuaEnvironment::createSimpleButton,
			&LuaEnvironment::createSimpleButtonLayout,
			&LuaEnvironment::createButton,
			&LuaEnvironment::createButtonLayout,
			&LuaEnvironment::createButtonAll
		),

		// Properties
		"enabled", sol::property(&LuaButton::setButtonEnabled),
		"onMouseEnter", sol::property(&LuaButton::setOnMouseEnter),
		"onMouseExit", sol::property(&LuaButton::setOnMouseExit),
		"onClick", sol::property(&LuaButton::setOnClick),

		// Functions

		// Base class
		sol::base_classes, sol::bases<LuaObject>()
	);

	// Register Text class
	lua.new_usertype<LuaText>("Text",
		// Constructor
		"new", sol::factories(createText),

		// Properties

		// Functions
		"setText", &LuaText::setText,

		// Base class
		sol::base_classes, sol::bases<LuaObject>()
	);

	// Register Character Sprite class
	lua.new_usertype<LuaCharacterSprite>("CharacterSprite",
		// Constructor
		"new", sol::factories(
			&LuaEnvironment::createCharacterSpriteSimple,
			&LuaEnvironment::createCharacterPosition,
			&LuaEnvironment::createCharacterPositionZindex,
			&LuaEnvironment::createCharacterVector,
			&LuaEnvironment::createCharacterVectorZindex
		),

		// Functions
		"show", sol::overload(
			&LuaCharacterSprite::show,
			&LuaCharacterSprite::showTransition
		),
		"hide", sol::overload(
			&LuaCharacterSprite::hide,
			&LuaCharacterSprite::hideTransition
		),
		"setBase", sol::overload(
			&LuaCharacterSprite::setBase,
			&LuaCharacterSprite::setBaseTransition
		),
		"setColorLUT", &LuaCharacterSprite::setColorLut,
		"disableColorGrading", &LuaCharacterSprite::disableColorGrading,
		"skipTransition", &LuaCharacterSprite::skipTransition,
		"setPosition", sol::overload(
			&LuaCharacterSprite::setPosition,
			&LuaCharacterSprite::setCharacterPosition
		),
		"setX", &LuaCharacterSprite::setPositionX,
		"move", sol::overload(
			&LuaCharacterSprite::moveInterpolator,
			&LuaCharacterSprite::move,
			&LuaCharacterSprite::movePositionInterpolator,
			&LuaCharacterSprite::movePosition
		),
		"moveX", sol::overload(
			&LuaCharacterSprite::moveXInterpolator,
			&LuaCharacterSprite::moveX
		),
		"setExpressionBase", &LuaCharacterSprite::setExpressionBase
	);

	// Register Cursor class
	lua.new_usertype<Cursor>("Cursor",
		// Constructor
		sol::constructors<Cursor(const std::string&, int, int)>()
	);

	// Register Clickable Map class
	lua.new_usertype<LuaClickableMap>("ClickableMap",
		// Constructor
		"new", sol::factories(
			&LuaEnvironment::createClickableMap
		),

		// Properties
		"disableOnClick", sol::property(&LuaClickableMap::setDisableOnClick),
		"nonBlocking", sol::property(&LuaClickableMap::setNonBlocking),

		// Functions
		"enable", &LuaClickableMap::enable,
		"disable", &LuaClickableMap::disable,
		"setOnMouseEnter", sol::overload(
			&LuaClickableMap::setOnMouseEnter,
			&LuaClickableMap::setOnMouseEnterRed
		),
		"setOnMouseExit", sol::overload(
			&LuaClickableMap::setOnMouseExit,
			&LuaClickableMap::setOnMouseExitRed
		),
		"setOnClick", sol::overload(
			&LuaClickableMap::setOnClick,
			&LuaClickableMap::setOnClickRed
		)
	);

	// Register functions
	lua.set_function("say", sol::overload(
		&LuaEnvironment::say,
		&LuaEnvironment::sayNumber
	));
	lua.set_function("append", &LuaEnvironment::append, this);
	lua.set_function("setBackground", sol::overload(
		&LuaEnvironment::setBackgroundTransition,
		&LuaEnvironment::setBackground
	));
	lua.set_function("scene", sol::overload(
		&LuaEnvironment::sceneTime,
		&LuaEnvironment::sceneTransition,
		&LuaEnvironment::scene
	));
	lua.set_function("hideText", &LuaEnvironment::hideText, this);
	lua.set_function("setTextAlign", &LuaEnvironment::setTextAlign, this);
	lua.set_function("disableSkip", &LuaEnvironment::disableSkip, this);
	lua.set_function("enableSkip", &LuaEnvironment::enableSkip, this);
	lua.set_function("disableMouseInput", &LuaEnvironment::disableMouseInput, this);
	lua.set_function("enableMouseInput", &LuaEnvironment::enableMouseInput, this);
	lua.set_function("playMusic", &LuaEnvironment::playMusic, this);
	lua.set_function("fadeInMusic", &LuaEnvironment::fadeInMusic, this);
	lua.set_function("stopMusic", &LuaEnvironment::stopMusic, this);
	lua.set_function("fadeOutMusic", &LuaEnvironment::fadeOutMusic, this);
	lua.set_function("playSound", &LuaEnvironment::playSound, this);
	lua.set_function("stopSound", &LuaEnvironment::stopSound, this);
	lua.set_function("yield", &LuaEnvironment::yield, this);
	lua.set_function("sleep", &LuaEnvironment::sleep, this);
	lua.set_function("getDeltaSeconds", &LuaEnvironment::getDeltaSeconds, this);
	lua.set_function("openScript", &LuaEnvironment::openScript, this);
	lua.set_function("precacheImage", &LuaEnvironment::precacheImage, this);
	lua.set_function("exitGame", &LuaEnvironment::exitGame, this);
	lua.set_function("saveScreenshot", &LuaEnvironment::saveScreenshot, this);
	lua.set_function("setCursor", &LuaEnvironment::setCursor, this);
	lua.set_function("setOnRightClick", &LuaEnvironment::setOnRightClick, this);

	// Register enums
	lua.new_enum("Position",
		"left", Alignment::LEFT,
		"center", Alignment::CENTER,
		"right", Alignment::RIGHT
	);

	lua.new_enum("Transition",
		"none", TransitionType::NONE,
		"fade", TransitionType::FADE,
		"dissolve", TransitionType::DISSOLVE,
		"imageDissolve", TransitionType::IMAGE_DISSOLVE
	);

	lua.new_enum("Interpolator",
		"linear", InterpolatorType::LINEAR,
		"easeIn", InterpolatorType::QUADRATIC_IN,
		"easeOut", InterpolatorType::QUADRATIC_OUT,
		"easeInOut", InterpolatorType::QUADRATIC_IN_OUT
	);

	// Load script
	loadScript(Config::values().game.startScript);
}


bool LuaEnvironment::ready()
{
	if (!nextScript.empty())
	{
		loadScript(nextScript);
		nextScript.clear();
	}

	// Check if there are runnable coroutines in the stack
	popNonRunnableCoroutines();

	bool isReady = !coroutineStack.empty() && coroutineStack.top().coroutine;

	// Check in order if all the conditions needed for Lua to resume execution are met
	while (isReady && !coroutineStack.top().waitQueue.empty())
	{
		WaitQueue& waitQueue = coroutineStack.top().waitQueue;
		WaitCommand* command = waitQueue.front();

		if (command->ready())
			waitQueue.pop();
		else
			isReady = false;
	}

	return isReady;
}

void LuaEnvironment::resume()
{
	// Calculate time since last Lua execution
	last = now;
	now = SDL_GetPerformanceCounter();

	// Execute all coroutines in the stack that are ready
	do {
		auto result = coroutineStack.top().coroutine();

		if (!result.valid())
		{
			sol::error err = result;

			Locator::getLogger()->log(
				LogCategory::LUA,
				LogPriority::ERROR,
				u8"Error executing script:\n" + std::string(err.what())
			);
		}

		// If the top coroutine has finished, execute the next one
		// Do not continue execution if the top coroutine has not finished
		// as that means it has yielded purposely
	} while (!coroutineStack.top().coroutine && ready());
}

bool LuaEnvironment::shouldExitGame()
{
	return wantsToExit;
}

void LuaEnvironment::execute(StorableFunction function)
{
	CoroutineThread thread;

	thread.runner = sol::thread::create(lua.lua_state());

	sol::function f = sol::function(thread.runner.state(), function.function);
	thread.coroutine = sol::coroutine(thread.runner.state(), sol::ref_index(f.registry_index()));

	executeCoroutine(thread);
}

void LuaEnvironment::waitFor(WaitCommand* command)
{
	coroutineStack.top().waitQueue.push(command);
}

LuaEnvironment::StorableFunction LuaEnvironment::storableFunction(sol::function function)
{
	StorableFunction f;
	f.coroutine = coroutineStack.top().coroutine;
	f.runner = coroutineStack.top().runner;
	f.function = function;

	return f;
}

void LuaEnvironment::loadScript(const std::string& file)
{
	CoroutineThread thread;

	thread.runner = sol::thread::create(lua.lua_state());
	sol::state_view runnerstate = thread.runner.state();
	sol::load_result loadedScript = runnerstate.load_file(file);

	if (!loadedScript.valid())
	{
		// Handle errors
		sol::error err = loadedScript;
		
		Locator::getLogger()->log(
			LogCategory::LUA,
			LogPriority::ERROR,
			u8"Error loading script:\n" + std::string(err.what())
		);
	}
	else
	{
		thread.coroutine = loadedScript;

		// After loadScript coroutine stack should be empty
		clearCoroutineStack();

		executeCoroutine(thread);
	}
}

void LuaEnvironment::clearCoroutineStack()
{
	while (!coroutineStack.empty())
		coroutineStack.pop();
}

void LuaEnvironment::popNonRunnableCoroutines()
{
	while (!coroutineStack.empty() && !coroutineStack.top().coroutine)
		coroutineStack.pop();
}

void LuaEnvironment::executeCoroutine(CoroutineThread coroutine)
{
	// If the current coroutine has finished, we can pop it to save memory
	popNonRunnableCoroutines();

	coroutineStack.push(coroutine);
}

void LuaEnvironment::say(const std::string& text, sol::this_state s)
{
	if (textWindow->visible())
	{
		textWindow->setText(text);

		// Wait until the player has read the text
		thisEnvironment->waitFor(new WaitForText(textWindow));
	}
	else
	{
		// Clear previous text
		textWindow->clearText();

		// Show text window
		textWindow->startFadeIn(Config::values().textWindow.showTransitionTime, true);

		// Wait for the transition to finish
		thisEnvironment->waitFor(new WaitForTransition(textWindow));

		// Wait until the player has read the text
		thisEnvironment->waitFor(new WaitForText(textWindow, text));
	}

	lua_yield(s, 0);
}

void LuaEnvironment::sayNumber(double number, sol::this_state s)
{
	std::string text = std::to_string(number);
	text.erase(text.find_last_not_of('0') + 1, std::string::npos);

	if (!text.empty() && text[text.size() - 1] == '.')
		text.pop_back();

	say(text, s);
}

void LuaEnvironment::append(const std::string& text, sol::this_state s)
{
	textWindow->append(text);

	// Wait until the player has read the text
	thisEnvironment->waitFor(new WaitForText(textWindow));
	lua_yield(s, 0);
}

void LuaEnvironment::setBackground(const std::string & file)
{
	// By default background transitions use a non-blocking 0.5 seconds dissolve
	background->startDissolveBackground(file, 0.5f, false);
}

void LuaEnvironment::setBackgroundTransition(const std::string& file, const sol::table& transition, sol::this_state s)
{
	TransitionType transitionType;

	if (TransitionUtils::getTransitionType(transition, transitionType))
	{
		switch (transitionType)
		{
		case TransitionType::NONE:
			background->setBackground(file);
			break;

		case TransitionType::DISSOLVE:
			float transitionTime;
			bool shouldBlock;

			if (TransitionUtils::getTransitionTime(transition, transitionTime) &&
				TransitionUtils::getTransitionBlocking(transition, shouldBlock))
			{
				background->startDissolveBackground(file, transitionTime, shouldBlock);

				if (shouldBlock)
				{
					thisEnvironment->waitFor(new WaitForTransition(background));
					lua_yield(s, 0);
				}
			}

			break;

		default:
			Locator::getLogger()->log(
				LogCategory::LUA,
				LogPriority::ERROR,
				u8"Invalid transition type for background change"
			);
			break;
		}
	}
}

void LuaEnvironment::scene(const std::string& file, sol::this_state s)
{
	// By default scene transitions use a blocking 0.5 seconds dissolve
	sceneTime(file, 0.5, s);
}

void LuaEnvironment::sceneTime(const std::string& file, float seconds, sol::this_state s)
{
	// Disable mouse input while in transition
	bool mouseInputEnabled = Locator::getInput()->getMouseInputEnabled();
	Locator::getInput()->setMouseInputEnabled(false);

	// Full path to the background
	std::string fullPath = Config::values().paths.backgrounds + file;

	// Lambda function that will start the transition
	auto executeTransition = [=]() {
		sceneTransitionEffect->setBackground(file);
		sceneTransitionEffect->startFadeIn(seconds, true);

		return true;
	};

	if (Config::values().cache.finishLoadingSceneTransitions
		&& !Locator::getCache()->isPresent(fullPath))
	{
		// Background is not in cache and needs to be preloaded
		Locator::getCache()->getSprite(fullPath);

		// Start scene transition next frame
		thisEnvironment->waitFor(new WaitForFunction(executeTransition));
	}
	else
	{
		// Start transition now
		executeTransition();
	}

	// Wait for transition and then clear the scene
	thisEnvironment->waitFor(new WaitForTransition(sceneTransitionEffect));
	thisEnvironment->waitFor(new ClearScene(gameObjectManager, background, file, mouseInputEnabled));
	lua_yield(s, 0);
}

void LuaEnvironment::sceneTransition(const std::string& file, const sol::table& transition, sol::this_state s)
{
	TransitionType transitionType;

	if (TransitionUtils::getTransitionType(transition, transitionType))
	{
		switch (transitionType)
		{
		case TransitionType::NONE:
			gameObjectManager->hideAll();
			background->setBackground(file);

			break;

		case TransitionType::DISSOLVE:
			float transitionTime;

			if (TransitionUtils::getTransitionTime(transition, transitionTime))
				sceneTime(file, transitionTime, s);

			break;

		case TransitionType::IMAGE_DISSOLVE:
		{
			// Disable mouse input while in transition
			bool mouseInputEnabled = Locator::getInput()->getMouseInputEnabled();
			Locator::getInput()->setMouseInputEnabled(false);

			float transitionTime;
			std::string image;

			if (TransitionUtils::getTransitionTime(transition, transitionTime) &&
				TransitionUtils::getTransitionImage(transition, image))
			{
				// Full paths to the images
				std::string backgroundFullPath = Config::values().paths.backgrounds + file;
				std::string transitionFullPath = Config::values().paths.transitions + image;

				// Lambda function that will start the transition
				auto executeTransition = [=]() {
					sceneTransitionEffect->setBackground(file);
					sceneTransitionEffect->startImageDissolve(transitionTime, image, true, renderer);

					return true;
				};

				ICache* cache = Locator::getCache();

				if (Config::values().cache.finishLoadingSceneTransitions
					&& (!cache->isPresent(backgroundFullPath) || !cache->isPresent(transitionFullPath)))
				{
					// Preload both the background and the transition image
					Locator::getCache()->getSprite(backgroundFullPath);
					Locator::getCache()->getSprite(transitionFullPath);

					// Start scene transition next frame
					thisEnvironment->waitFor(new WaitForFunction(executeTransition));
				}
				else
				{
					// Start transition now
					executeTransition();
				}

				// Wait for transition and then clear the scene
				thisEnvironment->waitFor(new WaitForTransition(sceneTransitionEffect));
				thisEnvironment->waitFor(new ClearScene(gameObjectManager, background, file, mouseInputEnabled));
				lua_yield(s, 0);
			}

			break;
		}

		default:
			Locator::getLogger()->log(
				LogCategory::LUA,
				LogPriority::ERROR,
				u8"Invalid transition type for scene change"
			);

			break;
		}
	}
}

void LuaEnvironment::hideText(sol::this_state s)
{
	textWindow->startFadeOut(Config::values().textWindow.hideTransitionTime, true);

	// Wait for the transition to finish
	waitFor(new WaitForTransition(textWindow));
	lua_yield(s, 0);
}

void LuaEnvironment::setTextAlign(Alignment align)
{
	textWindow->setTextAlign(align);
}

void LuaEnvironment::disableSkip()
{
	Locator::getInput()->setAllowSkipping(false);
}

void LuaEnvironment::enableSkip()
{
	Locator::getInput()->setAllowSkipping(true);
}

void LuaEnvironment::disableMouseInput()
{
	Locator::getInput()->setMouseInputEnabled(false);
}

void LuaEnvironment::enableMouseInput()
{
	Locator::getInput()->setMouseInputEnabled(true);
}

void LuaEnvironment::playMusic(const std::string& file)
{
	Locator::getAudio()->playMusic(Config::values().paths.music + file);
}

void LuaEnvironment::fadeInMusic(const std::string& file, float seconds)
{
	Locator::getAudio()->fadeInMusic(Config::values().paths.music + file, seconds);
}

void LuaEnvironment::stopMusic()
{
	Locator::getAudio()->stopMusic();
}

void LuaEnvironment::fadeOutMusic(float seconds)
{
	Locator::getAudio()->fadeOutMusic(seconds);
}

void LuaEnvironment::playSound(const std::string& file)
{
	Locator::getAudio()->playSound(Config::values().paths.sounds + file);
}

void LuaEnvironment::stopSound(const std::string& file)
{
	Locator::getAudio()->stopSound(Config::values().paths.sounds + file);
}

void LuaEnvironment::yield(sol::this_state s)
{
	lua_yield(s, 0);
}

void LuaEnvironment::sleep(float seconds, sol::this_state s)
{
	gameObjectManager->startTimer(seconds);
	waitFor(new WaitForTimer(gameObjectManager));
	lua_yield(s, 0);
}

float LuaEnvironment::getDeltaSeconds()
{
	return ((now - last) / (float)SDL_GetPerformanceFrequency());
}

void LuaEnvironment::openScript(const std::string& file, sol::this_state s)
{
	// Hide all objects except for the background
	bool visible = background->visible();
	gameObjectManager->hideAll();
	background->setVisible(visible);

	nextScript = Config::values().paths.scripts + file;
	lua_yield(s, 0);
}

void LuaEnvironment::precacheImage(const std::string& file)
{
	Locator::getCache()->getSprite(file);
}

void LuaEnvironment::exitGame(sol::this_state s)
{
	wantsToExit = true;
	lua_yield(s, 0);
}

void LuaEnvironment::saveScreenshot(const std::string& path, int w, int h)
{
	renderer->saveScreenshot(path, w, h);
}

void LuaEnvironment::setCursor(Cursor* cursor)
{
	Locator::getInput()->setCursor(cursor);
}

void LuaEnvironment::setOnRightClick(sol::function function)
{
	if (function != sol::nil)
	{
		StorableFunction f = storableFunction(function);

		Locator::getInput()->setOnRightClick([=]() {
			execute(f);
		});
	}
	else
	{
		// If the function is nil, set the delegate to an empty function
		Locator::getInput()->setOnRightClick(std::function<void(void)>());
	}
}

LuaCharacter LuaEnvironment::createCharacter(const std::string& name)
{
	return LuaCharacter(name, textWindow, thisEnvironment);
}

LuaQuestion LuaEnvironment::createQuestion(const sol::table& choices)
{
	return LuaQuestion(thisEnvironment, choicesMenu, textWindow, choices);
}

LuaEnvironment::SpritePtr LuaEnvironment::createSpriteSimple(const std::string& file, int zindex)
{
	return SpritePtr(new LuaSprite(gameObjectManager, thisEnvironment, new SpriteObject(file, zindex)));
}

LuaEnvironment::ButtonPtr LuaEnvironment::createSimpleButton(const std::string& file, int zindex)
{
	return ButtonPtr(new LuaButton(gameObjectManager, thisEnvironment, new ButtonObject(file, zindex)));
}

LuaEnvironment::ButtonPtr LuaEnvironment::createSimpleButtonLayout(const std::string& file, int zindex, bool useVerticalLayout)
{
	return ButtonPtr(new LuaButton(gameObjectManager, thisEnvironment, new ButtonObject(file, zindex, useVerticalLayout)));
}

LuaEnvironment::ButtonPtr LuaEnvironment::createButton(const std::string& file, int zindex, const std::string& text)
{
	return ButtonPtr(new LuaButton(gameObjectManager, thisEnvironment, new ButtonObject(renderer, file, zindex, text)));
}

LuaEnvironment::ButtonPtr LuaEnvironment::createButtonLayout(const std::string& file, int zindex, const std::string& text, bool useVerticalLayout)
{
	return ButtonPtr(new LuaButton(gameObjectManager, thisEnvironment, new ButtonObject(renderer, file, zindex, text, useVerticalLayout)));
}

LuaEnvironment::ButtonPtr LuaEnvironment::createButtonAll(
	const std::string& file,
	int zindex,
	const std::string& text,
	bool useVerticalLayout,
	const sol::table& font,
	const sol::table& disabledColor,
	const sol::table& disabledShadowColor
)
{
	FontProperties fontProperties;
	fontProperties.fontFile = font["file"];
	fontProperties.fontSize = font["size"];
	fontProperties.fontColor = Color(font["color"]["r"], font["color"]["g"], font["color"]["b"], font["color"]["a"]);
	fontProperties.shadowDistance = font["shadowDistance"];
	fontProperties.shadowColor = Color(font["shadowColor"]["r"], font["shadowColor"]["g"], font["shadowColor"]["b"], font["shadowColor"]["a"]);

	Color disabled;
	disabled.r = disabledColor["r"];
	disabled.g = disabledColor["g"];
	disabled.b = disabledColor["b"];
	disabled.a = disabledColor["a"];

	Color disabledShadow;
	disabledShadow.r = disabledShadowColor["r"];
	disabledShadow.g = disabledShadowColor["g"];
	disabledShadow.b = disabledShadowColor["b"];
	disabledShadow.a = disabledShadowColor["a"];

	return ButtonPtr(
		new LuaButton(
			gameObjectManager,
			thisEnvironment,
			new ButtonObject(
				renderer,
				file,
				zindex,
				text,
				useVerticalLayout,
				fontProperties,
				disabled,
				disabledShadow
			)
		)
	);
}

LuaEnvironment::LuaTextPtr LuaEnvironment::createText(const sol::table& font, int zindex)
{
	FontProperties fontProperties;
	fontProperties.fontFile = font["file"];
	fontProperties.fontSize = font["size"];
	fontProperties.fontColor = Color(font["color"]["r"], font["color"]["g"], font["color"]["b"], font["color"]["a"]);
	fontProperties.shadowDistance = font["shadowDistance"];
	fontProperties.shadowColor = Color(font["shadowColor"]["r"], font["shadowColor"]["g"], font["shadowColor"]["b"], font["shadowColor"]["a"]);

	return LuaTextPtr(new LuaText(gameObjectManager, thisEnvironment, new TextObject(fontProperties, zindex)));
}

LuaEnvironment::CharacterSpritePtr LuaEnvironment::createCharacterSpriteSimple(const std::string& file)
{
	return CharacterSpritePtr(new LuaCharacterSprite(renderer, gameObjectManager, thisEnvironment, file));
}

LuaEnvironment::CharacterSpritePtr LuaEnvironment::createCharacterPosition(const std::string& file, Alignment position)
{
	return CharacterSpritePtr(new LuaCharacterSprite(renderer, gameObjectManager, thisEnvironment, file, position));
}

LuaEnvironment::CharacterSpritePtr LuaEnvironment::createCharacterPositionZindex(const std::string& file, Alignment position, int zindex)
{
	return CharacterSpritePtr(new LuaCharacterSprite(renderer, gameObjectManager, thisEnvironment, file, position, zindex));
}

LuaEnvironment::CharacterSpritePtr LuaEnvironment::createCharacterVector(const std::string& file, const sol::table& position)
{
	return CharacterSpritePtr(new LuaCharacterSprite(renderer, gameObjectManager, thisEnvironment, file, Vector2<float>(position["x"], position["y"])));
}

LuaEnvironment::CharacterSpritePtr LuaEnvironment::createCharacterVectorZindex(const std::string& file, const sol::table& position, int zindex)
{
	return CharacterSpritePtr(new LuaCharacterSprite(renderer, gameObjectManager, thisEnvironment, file, Vector2<float>(position["x"], position["y"]), zindex));
}

LuaEnvironment::ClickableMapPtr LuaEnvironment::createClickableMap(const std::string& file)
{
	return ClickableMapPtr(new LuaClickableMap(gameObjectManager, thisEnvironment, file));
}
