#pragma once

#include "Vector.h"
#include "InterpolatorType.h"
#include <sol.hpp>

class LuaObject
{
public:
	LuaObject(
		class GameObjectManager* gameObjectManager,
		class LuaEnvironment* lua,
		class Object* object
	);
	virtual ~LuaObject();

	void show();
	void showTransition(const sol::table& transition, sol::this_state s);
	void hide();
	void hideTransition(const sol::table& transition, sol::this_state s);
	void setAlpha(uint8_t alpha);
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

	bool getVisible();

protected:
	Object* getObject();
	class LuaEnvironment* getLua();

private:
	class GameObjectManager* gameObjectManager;
	class LuaEnvironment* lua;
	class Object* object;
};