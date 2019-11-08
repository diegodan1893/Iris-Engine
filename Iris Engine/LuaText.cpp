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

void LuaText::setMaxWidth(int width, const std::string& ellipsis)
{
	((TextObject*)getObject())->setMaxWidth(width, ellipsis);
}

int LuaText::getWidth()
{
	return ((TextObject*)getObject())->getWidth();
}
