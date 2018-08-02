#pragma once

#include <sol.hpp>
#include <vector>
#include <string>

class LuaQuestion
{
public:
	LuaQuestion(
		class LuaEnvironment* lua,
		class ButtonMenu* menu,
		class TextWindow* textWindow,
		const sol::table& choices
	);

	void ask(sol::this_state s);

	sol::object getAnswer();
	void setAnswer(std::size_t index);

	bool getRemoveAfterSelection() const;
	void setRemoveAfterSelection(bool removeAfterSelection);

	std::size_t count() const;

private:
	class LuaEnvironment* lua;
	class ButtonMenu* menu;
	class TextWindow* textWindow;

	std::size_t selectedOption;
	sol::object selectedObject;
	bool removeAfterSelection;

	std::vector<std::string> choicesText;
	std::vector<sol::object> choicesResults;
};