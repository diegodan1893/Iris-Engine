#pragma once

#include <sol.hpp>
#include <string>

class LuaCharacter
{
public:
	LuaCharacter(const std::string& name, class TextWindow* textWindow, class LuaEnvironment* lua);

	void say(const std::string& text, sol::this_state s) const;
	void sayNumber(double number, sol::this_state s) const;
	void setName(const std::string& name);
	const std::string& getName();

private:
	std::string name;
	class TextWindow* textWindow;
	class LuaEnvironment* lua;
};