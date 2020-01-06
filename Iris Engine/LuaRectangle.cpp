#include "LuaRectangle.h"
#include "RectangleObject.h"

LuaRectangle::LuaRectangle(GameObjectManager* gameObjectManager, LuaEnvironment* lua, RectangleObject* object)
	:LuaObject(gameObjectManager, lua, object)
{
}

LuaRectangle::~LuaRectangle()
{
}

void LuaRectangle::setSize(int w, int h)
{
	((RectangleObject*)getObject())->setRectangleSize(w, h);
}

void LuaRectangle::setColor(sol::table color)
{
	Color rectColor;
	rectColor.r = color["r"];
	rectColor.g = color["g"];
	rectColor.b = color["b"];
	rectColor.a = color["a"];

	((RectangleObject*)getObject())->setColor(rectColor);
}
