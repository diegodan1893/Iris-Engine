#include "LuaQuestion.h"
#include "ButtonMenu.h"
#include "TextWindow.h"
#include "Locator.h"
#include "WaitQueue.h"
#include "WaitForChoice.h"
#include "LuaEnvironment.h"
#include <string>

LuaQuestion::LuaQuestion(LuaEnvironment* lua, ButtonMenu* menu, TextWindow* textWindow, const sol::table& choices)
	:lua(lua),
	 menu(menu),
	 textWindow(textWindow),
	 selectedOption(0),
	 removeAfterSelection(false)
{
	int count = choices.size();

	if (count > 0 && count % 2 == 0)
	{
		// Lua expects iteration to work in the range of [1, count]
		for (int i = 1; i <= count; i += 2)
		{
			// Odd elements are strings for the choices
			choicesText.push_back(choices[i]);

			// Even numbers are the result of the choices
			choicesResults.push_back(choices[i + 1]);
		}
	}
	else
	{
		Locator::getLogger()->log(
			LogCategory::LUA,
			LogPriority::ERROR,
			u8"Mismatching number of choices and outcomes or one of the answers is 'nil'"
		);
	}
}

void LuaQuestion::ask(sol::this_state s)
{
	menu->show(choicesText);
	textWindow->enterQuestionMode();

	lua->waitFor(new WaitForChoice(menu, this));
	lua_yield(s, 0);
}

sol::object LuaQuestion::getAnswer()
{
	return selectedObject;
}

void LuaQuestion::setAnswer(std::size_t index)
{
	selectedOption = index;
	selectedObject = choicesResults[selectedOption];

	// If the result is a function, execute it
	if (choicesResults[selectedOption].is<sol::function>())
	{
		// Lua garbage collector can't collect this function because
		// the Question must be accesible to the lua scripts for the
		// user to be able to call LuaQuestion::ask()
		LuaEnvironment::StorableFunction f = lua->storableFunction(choicesResults[selectedOption]);
		lua->execute(f);
	}

	if (removeAfterSelection)
	{
		choicesText.erase(choicesText.begin() + selectedOption);
		choicesResults.erase(choicesResults.begin() + selectedOption);
	}
}

bool LuaQuestion::getRemoveAfterSelection() const
{
	return removeAfterSelection;
}

void LuaQuestion::setRemoveAfterSelection(bool removeAfterSelection)
{
	this->removeAfterSelection = removeAfterSelection;
}

std::size_t LuaQuestion::count() const
{
	return choicesText.size();
}
