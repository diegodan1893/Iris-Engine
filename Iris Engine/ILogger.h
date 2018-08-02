#pragma once

#include <string>

/// <summary>
/// Categories supported by the logger.
/// </summary>
enum class LogCategory
{
	SYSTEM,
	AUDIO,
	VIDEO,
	RENDER,
	INPUT,
	TEST,
	LUA,
	CACHE,
	OBJECT,
	FILE
};

/// <summary>
/// Priority of the log event.
/// </summary>
enum class LogPriority
{
	INFO,
	WARNING,
	ERROR
};

/// <summary>
/// Logging service.
/// </summary>
class ILogger
{
public:
	virtual ~ILogger() {}
	
	/// <summary>
	/// Logs the specified message.
	/// </summary>
	/// <param name="category">The category of the log.</param>
	/// <param name="priority">The priority of the message.</param>
	/// <param name="text">The text to log.</param>
	virtual void log(LogCategory category, LogPriority priority, std::string text) = 0;
};