#include "LuaClickableMap.h"
#include "ClickableMap.h"
#include "GameObjectManager.h"
#include "LuaEnvironment.h"
#include "WaitForVisible.h"

LuaClickableMap::LuaClickableMap(GameObjectManager* gameObjectManager, LuaEnvironment* lua, const std::string& file)
	:gameObjectManager(gameObjectManager),
	 lua(lua)
{
	// Create map
	map = new ClickableMap(file);

	// Add map to game object manager
	gameObjectManager->add(map);
}

LuaClickableMap::~LuaClickableMap()
{
	bool success = gameObjectManager->remove(map);

	if (success)
		delete map;
}

void LuaClickableMap::enable(sol::this_state s)
{
	map->setVisible(true);

	// Wait until the map is not visible
	lua->waitFor(new WaitForVisible(map, false));
	lua_yield(s, 0);
}

void LuaClickableMap::disable()
{
	map->setVisible(false);
}

void LuaClickableMap::setDisableOnClick(bool disableOnClick)
{
	map->setDisableOnClick(disableOnClick);
}

void LuaClickableMap::setOnMouseEnter(int r, int g, int b, sol::function function)
{
	if (function != sol::nil)
	{
		LuaEnvironment::StorableFunction f = lua->storableFunction(function);

		map->setOnMouseEnter(r, g, b, [=]() {
			lua->execute(f);
		});
	}
	else
	{
		map->setOnMouseEnter(r, g, b, std::function<void(void)>());
	}
}

void LuaClickableMap::setOnMouseExit(int r, int g, int b, sol::function function)
{
	if (function != sol::nil)
	{
		LuaEnvironment::StorableFunction f = lua->storableFunction(function);

		map->setOnMouseExit(r, g, b, [=]() {
			lua->execute(f);
		});
	}
	else
	{
		map->setOnMouseExit(r, g, b, std::function<void(void)>());
	}
}

void LuaClickableMap::setOnClick(int r, int g, int b, sol::function function)
{
	if (function != sol::nil)
	{
		LuaEnvironment::StorableFunction f = lua->storableFunction(function);

		map->setOnClick(r, g, b, [=]() {
			lua->execute(f);
		});
	}
	else
	{
		map->setOnClick(r, g, b, std::function<void(void)>());
	}
}

void LuaClickableMap::setOnMouseEnterRed(int r, sol::function function)
{
	setOnMouseEnter(r, 0, 0, function);
}

void LuaClickableMap::setOnMouseExitRed(int r, sol::function function)
{
	setOnMouseExit(r, 0, 0, function);
}

void LuaClickableMap::setOnClickRed(int r, sol::function function)
{
	setOnClick(r, 0, 0, function);
}
