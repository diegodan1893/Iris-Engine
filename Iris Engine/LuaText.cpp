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

void LuaText::setMaxSize(int width, int height)
{
	((TextObject*)getObject())->setMaxSize(width, height);
}

void LuaText::setEllipsis(const std::string& ellipsis)
{
	((TextObject*)getObject())->setEllipsis(ellipsis);
}

void LuaText::setSpacing(int spacing)
{
	((TextObject*)getObject())->setSpacing(spacing);
}
