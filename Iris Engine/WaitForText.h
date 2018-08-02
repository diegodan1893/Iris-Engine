#pragma once

#include "WaitCommand.h"
#include <string>

/// <summary>
/// Waits until the player has skipped the current
/// message in the text window.
/// If a message is given, it will first display
/// that text on the textWindow and then wait for
/// the player to skip it.
/// </summary>
/// <seealso cref="WaitCommand" />
class WaitForText : public WaitCommand
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="WaitForText"/> class
	/// that only waits for the player to skip the current message.
	/// </summary>
	/// <param name="textWindow">The text window.</param>
	WaitForText(class TextWindow* textWindow);
	
	/// <summary>
	/// Initializes a new instance of the <see cref="WaitForText"/> class
	/// that will set the message of the text window when
	/// evaluated for the first time.
	/// </summary>
	/// <param name="textWindow">The text window.</param>
	/// <param name="text">The text.</param>
	WaitForText(class TextWindow* textWindow, const std::string& text);
	
	/// <summary>
	/// Initializes a new instance of the <see cref="WaitForText"/> class
	/// that will set the message of the text window and the
	/// displayed name when evaluated for the first time.
	/// </summary>
	/// <param name="textWindow">The text window.</param>
	/// <param name="name">The name of the speaker.</param>
	/// <param name="text">The text.</param>
	WaitForText(class TextWindow* textWindow, const std::string& name, const std::string& text);
	
	/// <summary>
	/// Check if the player has skipped the message
	/// on the text window.
	/// If a message was specified, it will display
	/// that message and return false the first time
	/// it's evaluated.
	/// </summary>
	/// <returns>
	///   <c>true</c> if the player has read the message; otherwise, <c>false</c>
	/// </returns>
	bool ready() override;

private:
	class TextWindow* textWindow;
	std::string text;
	std::string name;
};