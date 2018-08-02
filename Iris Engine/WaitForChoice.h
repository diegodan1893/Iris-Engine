#pragma once

#include "WaitCommand.h"
#include <vector>
#include <sol.hpp>

/// <summary>
/// Wait until the player has chosen an option
/// from a LuaQuestion.
/// </summary>
/// <seealso cref="WaitCommand" />
class WaitForChoice : public WaitCommand
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="WaitForChoice"/> class.
	/// </summary>
	/// <param name="menu">The menu object.</param>
	/// <param name="question">The LuaQuestion.</param>
	WaitForChoice(class ButtonMenu* menu, class LuaQuestion* question);
	
	/// <summary>
	/// Check if the player has chosen an option
	/// and notifies the LuaQuestion with the
	/// selected answer.
	/// </summary>
	/// <returns>
	///   <c>true</c> if the an option has been chosen; otherwise, <c>false</c>
	/// </returns>
	bool ready() override;

private:
	class ButtonMenu* menu;
	class LuaQuestion* question;
};