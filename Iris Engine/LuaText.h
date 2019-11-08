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
	void setMaxWidth(int width, const std::string& ellipsis);
	int getWidth();
};