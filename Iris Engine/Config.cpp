#include "Config.h"
#include "Locator.h"

Config::Values Config::configValues;
bool Config::valid = true;

bool Config::load(const std::string& file)
{

	// Load and parse config script
	sol::state config;
	config.script_file(file, &Config::luaError);

	if (valid)
	{
		try
		{
			// Game settings
			configValues.game.name = config["game"]["name"];
			configValues.game.iconFile = config["game"]["iconFile"];
			configValues.game.startScript = config["game"]["startScript"];

			// Screen settings
			configValues.screen.fullscreen = config["screen"]["fullscreen"];
			configValues.screen.resolution.x = config["screen"]["resolution"]["x"];
			configValues.screen.resolution.y = config["screen"]["resolution"]["y"];

			// Text window settings
			configValues.textWindow.position.x = config["textWindow"]["position"]["x"];
			configValues.textWindow.position.y = config["textWindow"]["position"]["y"];
			configValues.textWindow.size.x = config["textWindow"]["size"]["w"];
			configValues.textWindow.size.y = config["textWindow"]["size"]["h"];
			configValues.textWindow.margin.top = config["textWindow"]["margin"]["top"];
			configValues.textWindow.margin.right = config["textWindow"]["margin"]["right"];
			configValues.textWindow.margin.bottom = config["textWindow"]["margin"]["bottom"];
			configValues.textWindow.margin.left = config["textWindow"]["margin"]["left"];

			configValues.textWindow.background = config["textWindow"]["background"];
			configValues.textWindow.backgroundAlpha = config["textWindow"]["backgroundAlpha"];

			configValues.textWindow.fontProperties.fontFile = config["textWindow"]["font"];
			configValues.textWindow.nameFontProperties.fontFile = config["textWindow"]["font"];
			configValues.textWindow.fontProperties.fontSize = config["textWindow"]["fontSize"];

			sol::table fontColor = config["textWindow"]["fontColor"];
			configValues.textWindow.fontProperties.fontColor = Color(
				fontColor["r"],
				fontColor["g"],
				fontColor["b"],
				fontColor["a"].get_or(255)
			);

			configValues.textWindow.fontProperties.shadowDistance = config["textWindow"]["shadowDistance"];

			sol::table shadowColor = config["textWindow"]["shadowColor"];
			configValues.textWindow.fontProperties.shadowColor = Color(
				shadowColor["r"],
				shadowColor["g"],
				shadowColor["b"],
				shadowColor["a"].get_or(255)
			);

			configValues.textWindow.spacing = config["textWindow"]["spacing"];
			configValues.textWindow.wordWrapping = config["textWindow"]["wordWrapping"];
			configValues.textWindow.formatJapaneseText = config["textWindow"]["formatJapaneseText"];
			configValues.textWindow.characterDelay = config["textWindow"]["characterDelay"];

			configValues.textWindow.namePos.x = config["textWindow"]["namePosition"]["x"];
			configValues.textWindow.namePos.y = config["textWindow"]["namePosition"]["y"];
			configValues.textWindow.nameFontProperties.fontSize = config["textWindow"]["nameFontSize"];

			sol::table nameFontColor = config["textWindow"]["nameFontColor"];
			configValues.textWindow.nameFontProperties.fontColor = Color(
				nameFontColor["r"],
				nameFontColor["g"],
				nameFontColor["b"],
				nameFontColor["a"].get_or(255)
			);

			configValues.textWindow.nameFontProperties.shadowDistance = config["textWindow"]["nameShadowDistance"];
			
			sol::table nameShadowColor = config["textWindow"]["nameShadowColor"];
			configValues.textWindow.nameFontProperties.shadowColor = Color(
				nameShadowColor["r"],
				nameShadowColor["g"],
				nameShadowColor["b"],
				nameShadowColor["a"].get_or(255)
			);

			configValues.textWindow.indicatorImage = config["textWindow"]["indicatorImage"];
			configValues.textWindow.indicatorPosition.x = config["textWindow"]["indicatorPosition"]["x"];
			configValues.textWindow.indicatorPosition.y = config["textWindow"]["indicatorPosition"]["y"];
			configValues.textWindow.showIndicatorAfterLastCharacter = config["textWindow"]["showIndicatorAfterLastCharacter"];
			
			sol::table indicatorSpriteSheet = config["textWindow"]["indicatorSpriteSheet"];
			configValues.textWindow.indicatorFrameCount = indicatorSpriteSheet["frameCount"];
			configValues.textWindow.indicatorCols = indicatorSpriteSheet["columns"];
			configValues.textWindow.indicatorRows = indicatorSpriteSheet["rows"];
			configValues.textWindow.indicatorFPS = indicatorSpriteSheet["fps"];
			
			configValues.textWindow.showTransitionTime = config["textWindow"]["showTransition"]["time"];
			configValues.textWindow.hideTransitionTime = config["textWindow"]["hideTransition"]["time"];

			// Choices settings
			configValues.choices.position.x = config["choices"]["position"]["x"];
			configValues.choices.position.y = config["choices"]["position"]["y"];
			configValues.choices.size.x = config["choices"]["size"]["w"];
			configValues.choices.size.y = config["choices"]["size"]["h"];
			configValues.choices.background = config["choices"]["background"];
			configValues.choices.useVerticalLayout = config["choices"]["useVerticalLayout"];
			configValues.choices.separation.x = config["choices"]["separation"]["x"];
			configValues.choices.separation.y = config["choices"]["separation"]["y"];

			configValues.choices.showTransitionTime = config["choices"]["showTransition"]["timePerButton"];
			configValues.choices.showTransitionDelay = config["choices"]["showTransition"]["timeBetweenButtons"];
			configValues.choices.hideTransitionTime = config["choices"]["hideTransition"]["time"];

			// Path settings
			configValues.paths.scripts = config["paths"]["scripts"];
			configValues.paths.sprites = config["paths"]["sprites"];
			configValues.paths.characters = config["paths"]["characters"];
			configValues.paths.backgrounds = config["paths"]["backgrounds"];
			configValues.paths.transitions = config["paths"]["transitions"];
			configValues.paths.gui = config["paths"]["gui"];
			configValues.paths.luts = config["paths"]["luts"];
			configValues.paths.music = config["paths"]["music"];
			configValues.paths.sounds = config["paths"]["sounds"];
			configValues.paths.separator = config["paths"]["separator"];

			// Sounds settings
			std::string buttonHover = config["sounds"]["buttonHoverSound"];
			configValues.sounds.buttonHoverSound = configValues.paths.sounds + buttonHover;

			std::string buttonClick = config["sounds"]["buttonClickSound"];
			configValues.sounds.buttonClickSound = configValues.paths.sounds + buttonClick;

			// Zindex settings
			configValues.zindexes.sceneTransitionEffects = config["zindexes"]["sceneTransitionEffects"];
			configValues.zindexes.textWindow = config["zindexes"]["textWindow"];
			configValues.zindexes.choices = config["zindexes"]["choices"];
			configValues.zindexes.characters = config["zindexes"]["characters"];
			configValues.zindexes.backgrounds = config["zindexes"]["backgrounds"];

			// Cache settings
			configValues.cache.maxSizeInMiB = config["cache"]["maxSizeInMiB"];
			configValues.cache.allowPrecaching = config["cache"]["allowPrecaching"];
			configValues.cache.finishLoadingSceneTransitions = config["cache"]["finishLoadingSceneTransitions"];


			// Create full path to start script
			configValues.game.startScript = configValues.paths.scripts + configValues.game.startScript;
		}
		catch (sol::error err)
		{
			Locator::getLogger()->log(
				LogCategory::LUA,
				LogPriority::ERROR,
				u8"Error reading config values:\n" + std::string(err.what()) + u8"\n\nDid you change the name of a key?"
			);

			valid = false;
		}
	}

	return valid;
}

const Config::Values& Config::values()
{
	return configValues;
}

sol::protected_function_result Config::luaError(lua_State* L, sol::protected_function_result pfr)
{
	std::string error = pfr;

	Locator::getLogger()->log(
		LogCategory::LUA,
		LogPriority::ERROR,
		u8"Error loading config file:\n" + error + u8"\n\nCheck around the specified line (the number after the name of the file) for errors."
	);

	valid = false;
	return pfr;
}
