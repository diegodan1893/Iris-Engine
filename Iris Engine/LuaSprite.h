#pragma once

#include "Vector.h"
#include "InterpolatorType.h"
#include <string>
#include <sol.hpp>

class LuaSprite
{
public:
	LuaSprite(
		class GameObjectManager* gameObjectManager,
		class LuaEnvironment* lua,
		class SpriteObject* object
	);
	virtual ~LuaSprite();

	void show();
	void showTransition(const sol::table& transition, sol::this_state s);
	void hide();
	void hideTransition(const sol::table& transition, sol::this_state s);
	void skipTransition();
	void setPosition(float x, float y);
	std::tuple<float, float> getPosition();
	void setOrigin(int x, int y);
	void move(float x, float y, float time, bool shouldBlock, sol::this_state s);
	void moveInterpolator(
		float x,
		float y,
		float time,
		bool shouldBlock,
		InterpolatorType interpolator,
		sol::this_state s
	);
	void defineSpriteSheet(int frameCount, int cols, int rows, int fps);
	void setFrame(int frame);

	bool getVisible();

protected:
	SpriteObject* getObject();

private:
	class GameObjectManager* gameObjectManager;
	class LuaEnvironment* lua;
	class SpriteObject* object;
};