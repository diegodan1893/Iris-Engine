#include "LuaCharacter.h"
#include "TextWindow.h"
#include "LuaEnvironment.h"
#include "WaitForText.h"
#include "WaitForTransition.h"
#include "Game.h"
#include <string>

LuaCharacter::LuaCharacter(const std::string& name, TextWindow* textWindow, LuaEnvironment* lua)
	:name(name),
	 textWindow(textWindow),
	 lua(lua)
{
}

void LuaCharacter::say(const std::string& text, sol::this_state s) const
{
	if (textWindow->visible())
	{
		textWindow->setText(name, text);

		// Wait until the player has read the text
		lua->waitFor(new WaitForText(textWindow));
	}
	else
	{
		// Clear previous text
		textWindow->clearText();

		// Show text window
		textWindow->startFadeIn(Config::values().textWindow.showTransitionTime, true);

		// Wait for the transition to finish
		lua->waitFor(new WaitForTransition(textWindow));

		// Wait until the player has read the text
		lua->waitFor(new WaitForText(textWindow, name, text));
	}

	lua_yield(s, 0);
}

void LuaCharacter::sayNumber(double number, sol::this_state s) const
{
	std::string text = std::to_string(number);
	text.erase(text.find_last_not_of('0') + 1, std::string::npos);

	if (!text.empty() && text[text.size() - 1] == '.')
		text.pop_back();

	say(text, s);
}

void LuaCharacter::setName(const std::string& name)
{
	this->name = name;
}

const std::string& LuaCharacter::getName()
{
	return name;
}
