#pragma once

#include "WaitQueue.h"
#include "LuaCharacter.h"
#include "LuaSprite.h"
#include "LuaButton.h"
#include "LuaQuestion.h"
#include "LuaCharacterSprite.h"
#include "LuaClickableMap.h"
#include <sol.hpp>
#include <stack>

/// <summary>
/// Handles Lua execution.
/// There can be only one instance of this class.
/// </summary>
class LuaEnvironment
{
public:
	class StorableFunction;

	LuaEnvironment();
	
	/// <summary>
	/// Sets up the Lua environment and registers classes and functions.
	/// </summary>
	/// <param name="renderer">The renderer.</param>
	/// <param name="textWindow">The text window.</param>
	/// <param name="gameObjectManager">The game object manager.</param>
	/// <param name="choicesMenu">The choices menu.</param>
	/// <param name="background">The background object.</param>
	/// <param name="sceneTransition">The scene transition effect object.</param>
	void setUp(
		class IRenderer* renderer,
		class TextWindow* textWindow,
		class GameObjectManager* gameObjectManager,
		class ButtonMenu* choicesMenu,
		class BackgroundObject* background,
		class BackgroundObject* sceneTransition
	);
		
	/// <summary>
	/// Check if the Lua execution can continue.
	/// If there are pending <see cref="WaitCommand">s
	/// in the queue, they will be evaluated until
	/// one of them returns false.
	/// </summary>
	/// <returns><c>true</c> if the Lua execution can continue; otherwise, <c>false</c>.</returns>
	bool ready();
	
	/// <summary>
	/// Resumes Lua execution until it yields.
	/// </summary>
	void resume();
	
	/// <summary>
	/// Check if the game has ended.
	/// </summary>
	/// <returns><c>true</c> if the program must be closed; otherwise <c>false</c>.</returns>
	bool shouldExitGame();
	
	/// <summary>
	/// Prepares the specified function to be executed
	/// the next time <see cref="resume"/> is called.
	/// </summary>
	/// <param name="function">The function to execute.</param>
	void execute(StorableFunction function);
	
	/// <summary>
	/// Adds a command to the wait queue of the current
	/// coroutine.
	/// </summary>
	/// <param name="command">The command.</param>
	void waitFor(WaitCommand* command);
	
	/// <summary>
	/// Creates a Lua function that can be safely stored.
	/// </summary>
	/// <param name="function">The function.</param>
	/// <returns></returns>
	StorableFunction storableFunction(sol::function function);

private:
	// Single instance
	static bool instantiated;
	static LuaEnvironment* thisEnvironment;

	// Other variables
	bool wantsToExit;
	uint64_t now, last;

	// Static variables needed for the Lua API
	static class IRenderer* renderer;
	static class GameObjectManager* gameObjectManager;
	static class TextWindow* textWindow;
	static class ButtonMenu* choicesMenu;
	static class BackgroundObject* background;
	static class BackgroundObject* sceneTransitionEffect;

	// Lua
	struct CoroutineThread {
		sol::coroutine coroutine;
		sol::thread runner;
		WaitQueue waitQueue;
	};
	
	/// <summary>
	/// The Lua state
	/// </summary>
	sol::state lua;
	
	/// <summary>
	/// A stack of coroutines that are pending
	/// execution. <see cref="resume"/> will
	/// execute the coroutine at the top until
	/// it has finished and continue with the
	/// next.
	/// </summary>
	std::stack<CoroutineThread> coroutineStack;
	
	/// <summary>
	/// Path to a script to load.
	/// </summary>
	std::string nextScript;

	// Helper fuctions	
	/// <summary>
	/// Loads a script for execution.
	/// The coroutine stack will be cleared.
	/// </summary>
	/// <param name="file">The file.</param>
	void loadScript(const std::string& file);
	
	/// <summary>
	/// Removes all the coroutines from the stack.
	/// </summary>
	void clearCoroutineStack();
	
	/// <summary>
	/// Pops non runnable coroutines from the stack.
	/// </summary>
	void popNonRunnableCoroutines();
	
	/// <summary>
	/// Inserts a coroutine in the stack.
	/// Non runnable coroutines at the top of the
	/// stack will be popped before the coroutine
	/// is inserted.
	/// </summary>
	/// <param name="coroutine">The coroutine.</param>
	void executeCoroutine(CoroutineThread coroutine);

	// Lua-exposed functions
	// Some functions are static because it's required for Lua binding
	static void say(const std::string& text, sol::this_state s);
	static void sayNumber(double number, sol::this_state s);
	void append(const std::string& text, sol::this_state s);
	static void setBackground(const std::string& file);
	static void setBackgroundTransition(const std::string& file, const sol::table& transition, sol::this_state s);
	static void scene(const std::string& file, sol::this_state s);
	static void sceneTime(const std::string& file, float seconds, sol::this_state s);
	static void sceneTransition(const std::string& file, const sol::table& transition, sol::this_state s);
	void hideText(sol::this_state s);
	void setTextAlign(Alignment align);
	void disableSkip();
	void enableSkip();
	void disableMouseInput();
	void enableMouseInput();
	void playMusic(const std::string& file);
	void fadeInMusic(const std::string& file, float seconds);
	void stopMusic();
	void fadeOutMusic(float seconds);
	void playSound(const std::string& file);
	void stopSound(const std::string& file);
	void yield(sol::this_state s);
	void sleep(float seconds, sol::this_state s);
	float getDeltaSeconds();
	void openScript(const std::string& file, sol::this_state s);
	void precacheImage(const std::string& file);
	void exitGame(sol::this_state s);
	void setCursor(class Cursor* cursor);
	void setOnRightClick(sol::function function);


	/** Factories **/
	// Characters
	static LuaCharacter createCharacter(const std::string& name);

	// Choices
	static LuaQuestion createQuestion(const sol::table& choices);

	// Sprite objects
	typedef std::unique_ptr<LuaSprite> SpritePtr;
	static SpritePtr createSpriteSimple(const std::string& file, int zindex);

	// Button objects
	typedef std::unique_ptr<LuaButton> ButtonPtr;
	static ButtonPtr createSimpleButton(const std::string& file, int zindex);
	static ButtonPtr createSimpleButtonLayout(const std::string& file, int zindex, bool useVerticalLayout);
	static ButtonPtr createButton(const std::string& file, int zindex, const std::string& text);
	static ButtonPtr createButtonLayout(const std::string& file, int zindex, const std::string& text, bool useVerticalLayout);

	// Character objects
	typedef std::unique_ptr<LuaCharacterSprite> CharacterSpritePtr;
	static CharacterSpritePtr createCharacterSpriteSimple(const std::string& file);
	static CharacterSpritePtr createCharacterPosition(const std::string& file, Alignment position);
	static CharacterSpritePtr createCharacterPositionZindex(const std::string& file, Alignment position, int zindex);
	static CharacterSpritePtr createCharacterVector(const std::string& file, const sol::table& position);
	static CharacterSpritePtr createCharacterVectorZindex(const std::string& file, const sol::table& position, int zindex);

	// Clickable map
	typedef std::unique_ptr<LuaClickableMap> ClickableMapPtr;
	static ClickableMapPtr createClickableMap(const std::string& file);

public:
	class StorableFunction
	{
	private:
		sol::thread runner;
		sol::coroutine coroutine;
		sol::function function;

		friend class LuaEnvironment;
	};
};