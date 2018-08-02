#pragma once

#include "ILogger.h"

/// <summary>
/// Logs with SDL_Log and shows a message box for
/// warnings and errors
/// </summary>
/// <seealso cref="ILogger" />
class MessageBoxLogger : public ILogger
{
public:	
	/// <summary>
	/// Logs the specified message.
	/// </summary>
	/// <param name="category">The category of the log.</param>
	/// <param name="priority">The priority of the message.</param>
	/// <param name="text">The text to log.</param>
	void log(LogCategory category, LogPriority priority, std::string text) override;
};