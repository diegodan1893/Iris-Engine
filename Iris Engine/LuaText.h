#pragma once

#include "LuaObject.h"
#include <string>

class LuaText : public LuaObject
{
public:
	LuaText(
		class GameObjectManager* gameObjectManager,
		class LuaEnvironment* lua,
		class TextObject* object
	);
	virtual ~LuaText() {}

	void setText(const std::string& text);
	int getWidth();
};