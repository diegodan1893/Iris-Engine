#include "LuaButton.h"
#include "ButtonObject.h"
#include "LuaEnvironment.h"

LuaButton::LuaButton(GameObjectManager* gameObjectManager, LuaEnvironment* lua, ButtonObject* object)
	:LuaObject(gameObjectManager, lua, object),
	 lua(lua)
{
}

LuaButton::~LuaButton()
{
}

void LuaButton::setButtonEnabled(bool enabled)
{
	((ButtonObject*)getObject())->setEnabled(enabled);
}

void LuaButton::setOnMouseEnter(sol::function function)
{
	if (function != sol::nil)
	{
		LuaEnvironment::StorableFunction f = lua->storableFunction(function);

		((ButtonObject*)getObject())->setOnMouseEnter([=](){
			lua->execute(f);
		});
	}
	else
	{
		// If the function is nil, set the delegate to an empty function
		((ButtonObject*)getObject())->setOnMouseEnter(std::function<void(void)>());
	}
}

void LuaButton::setOnMouseExit(sol::function function)
{
	if (function != sol::nil)
	{
		LuaEnvironment::StorableFunction f = lua->storableFunction(function);

		((ButtonObject*)getObject())->setOnMouseExit([=]() {
			lua->execute(f);
		});
	}
	else
	{
		// If the function is nil, set the delegate to an empty function
		((ButtonObject*)getObject())->setOnMouseExit(std::function<void(void)>());
	}
}

void LuaButton::setOnClick(sol::function function)
{
	if (function != sol::nil)
	{
		LuaEnvironment::StorableFunction f = lua->storableFunction(function);

		((ButtonObject*)getObject())->setOnClick([=]() {
			lua->execute(f);
		});
	}
	else
	{
		// If the function is nil, set the delegate to an empty function
		((ButtonObject*)getObject())->setOnClick(std::function<void(void)>());
	}
}
