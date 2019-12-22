#pragma once

#include "LuaObject.h"

class LuaRectangle : public LuaObject
{
public:
	LuaRectangle(
		class GameObjectManager* gameObjectManager,
		class LuaEnvironment* lua,
		class RectangleObject* object
	);
	virtual ~LuaRectangle();

	void setSize(int w, int h);
	void setColor(sol::table color);
};