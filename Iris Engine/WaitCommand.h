#pragma once

/// <summary>
/// A command used to pause Lua execution until
/// a condition is met.
/// It can optionally perform some actions when
/// that condition is met.
/// </summary>
class WaitCommand
{
public:
	virtual ~WaitCommand() {}
	
	/// <summary>
	/// Check if the condition has been met.
	/// </summary>
	/// <returns><c>true</c> if the condition has been met; otherwise, <c>false</c></returns>
	virtual bool ready() = 0;
};