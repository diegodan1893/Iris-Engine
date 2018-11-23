#pragma once

#include "Vector.h"
#include "Alignment.h"
#include "InterpolatorType.h"
#include "Config.h"

class LuaCharacterSprite
{
public:
	LuaCharacterSprite(
		class IRenderer* renderer,
		class GameObjectManager* gameObjectManager,
		class LuaEnvironment* lua,
		const std::string& baseFile,
		Alignment position = Alignment::CENTER,
		int zindex = Config::values().zindexes.characters
	);

	LuaCharacterSprite(
		class IRenderer* renderer,
		class GameObjectManager* gameObjectManager,
		class LuaEnvironment* lua,
		const std::string& baseFile,
		Vector2<float> position,
		int zindex = Config::values().zindexes.characters
	);

	~LuaCharacterSprite();

	void show(const std::string& expression);
	void showTransition(const std::string& expression, const sol::table& transition, sol::this_state s);
	void hide();
	void hideTransition(const sol::table& transition, sol::this_state s);
	void setBase(const std::string& base, const std::string& expressionBase, const std::string& expression);
	void setBaseTransition(
		const std::string& base,
		const std::string& expressionBase,
		const std::string& expression,
		const sol::table& transition,
		sol::this_state s
	);
	void setColorLut(const std::string& colorLUT, float time);
	void disableColorGrading(float time);
	void skipTransition();
	void setPosition(float x, float y);
	void setPositionX(float x);
	void setCharacterPosition(Alignment position);
	void move(float x, float y, float time, bool shouldBlock, sol::this_state s);
	void moveInterpolator(
		float x,
		float y,
		float time,
		bool shouldBlock,
		InterpolatorType interpolator,
		sol::this_state s
	);
	void moveX(float x, float time, bool shouldBlock, sol::this_state s);
	void moveXInterpolator(
		float x,
		float time,
		bool shouldBlock,
		InterpolatorType interpolator,
		sol::this_state s
	);
	void movePosition(Alignment position, float time, bool shouldBlock, sol::this_state s);
	void movePositionInterpolator(
		Alignment position,
		float time,
		bool shouldBlock,
		InterpolatorType interpolator,
		sol::this_state s
	);
	void setExpressionBase(const std::string& expressionBase);

private:
	class GameObjectManager* gameObjectManager;
	class LuaEnvironment* lua;
	class CharacterObject* character;
};