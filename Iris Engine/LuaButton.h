#pragma once

#include "LuaObject.h"

class LuaButton : public LuaObject
{
public:
	LuaButton(
		class GameObjectManager* gameObjectManager,
		class LuaEnvironment* lua,
		class ButtonObject* object
	);
	virtual ~LuaButton();

	void setButtonEnabled(bool enabled);
	void setOnMouseEnter(sol::function function);
	void setOnMouseExit(sol::function function);
	void setOnClick(sol::function function);

private:
	class LuaEnvironment* lua;
};
