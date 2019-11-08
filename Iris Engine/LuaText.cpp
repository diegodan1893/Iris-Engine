#include "LuaText.h"
#include "TextObject.h"

LuaText::LuaText(GameObjectManager* gameObjectManager, LuaEnvironment* lua, TextObject* object)
	:LuaObject(gameObjectManager, lua, object)
{
}

void LuaText::setText(const std::string& text)
{
	((TextObject*)getObject())->setText(text);
}

int LuaText::getWidth()
{
	return ((TextObject*)getObject())->getWidth();
}
