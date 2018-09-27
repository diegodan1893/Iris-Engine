#pragma once

#include <string>
#include <sol.hpp>

class LuaClickableMap
{
public:
	LuaClickableMap(
		class GameObjectManager* gameObjectManager,
		class LuaEnvironment* lua,
		const std::string& file
	);
	~LuaClickableMap();

	void enable(sol::this_state s);
	void disable();

	void setDisableOnClick(bool disableOnClick);
	void setNonBlocking(bool nonBlocking);

	void setOnMouseEnter(int r, int g, int b, sol::function function);
	void setOnMouseExit(int r, int g, int b, sol::function function);
	void setOnClick(int r, int g, int b, sol::function function);

	void setOnMouseEnterRed(int r, sol::function function);
	void setOnMouseExitRed(int r, sol::function function);
	void setOnClickRed(int r, sol::function function);

private:
	class GameObjectManager* gameObjectManager;
	class LuaEnvironment* lua;
	class ClickableMap* map;

	bool nonBlocking;
};