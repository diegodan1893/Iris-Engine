#pragma once

#include "FontProperties.h"
#include <sol.hpp>

/// <summary>
/// Stores the configuration of the engine.
/// </summary>
class Config
{
private:
	struct Game
	{
		std::string name;
		std::string iconFile;
		std::string startScript;
	};

	struct Screen
	{
		bool fullscreen;
		Vector2<unsigned int> resolution;
	};

	struct TextWindow
	{
		Vector2<int> position;
		Vector2<unsigned int> size;
		Margin margin;

		std::string background;
		uint8_t backgroundAlpha;

		FontProperties fontProperties;

		int spacing;
		bool wordWrapping;
		bool formatJapaneseText;
		float characterDelay;

		Vector2<int> namePos;

		FontProperties nameFontProperties;

		std::string indicatorImage;
		Vector2<int> indicatorPosition;
		bool showIndicatorAfterLastCharacter;
		int indicatorFrameCount;
		int indicatorCols;
		int indicatorRows;
		int indicatorFPS;

		// Transitions
		float showTransitionTime;
		float hideTransitionTime;
	};

	struct Choices
	{
		Vector2<int> position;
		Vector2<int> size;
		std::string background;
		bool useVerticalLayout;
		Vector2<int> separation;

		// Transitions
		float showTransitionTime;
		float showTransitionDelay;
		float hideTransitionTime;
	};

	struct Paths
	{
		std::string scripts;
		std::string sprites;
		std::string characters;
		std::string backgrounds;
		std::string transitions;
		std::string gui;
		std::string luts;
		std::string music;
		std::string sounds;
		std::string videos;
		std::string separator;
	};

	struct Sounds
	{
		std::string buttonHoverSound;
		std::string buttonClickSound;
	};

	struct Zindexes
	{
		int sceneTransitionEffects;
		int textWindow;
		int choices;
		int characters;
		int backgrounds;
	};

	struct Cache
	{
		unsigned int maxSizeInMiB;
		bool allowPrecaching;
		bool finishLoadingSceneTransitions;
	};

	struct Values
	{
		Game game;
		Screen screen;
		TextWindow textWindow;
		Choices choices;
		Paths paths;
		Sounds sounds;
		Zindexes zindexes;
		Cache cache;
	};

public:
	 /// <summary>
	 /// Reads the config file and stores its values
	 /// </summary>
	 /// <param name="file">The file.</param>
	 /// <returns><c>true</c> if the config was successfully loaded, <c>false</c> otherwise.</returns>
	static bool load(const std::string& file);
		
	/// <summary>
	/// Gets the config values.
	/// </summary>
	/// <returns>A const reference to the config values.</returns>
	static const Values& values();

private:
	static Values configValues;
	static bool valid;
	
	/// <summary>
	/// A function called when there is an
	/// error executing the config script.
	/// </summary>
	static sol::protected_function_result luaError(lua_State* L, sol::protected_function_result pfr);
};