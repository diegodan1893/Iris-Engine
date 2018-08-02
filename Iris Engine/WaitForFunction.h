#pragma once

#include "WaitCommand.h"
#include <functional>

/// <summary>
/// Wait until the given callback function returns true.
/// </summary>
/// <seealso cref="WaitCommand" />
class WaitForFunction : public WaitCommand
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="WaitForFunction"/> class.
	/// </summary>
	/// <param name="function">The function.</param>
	WaitForFunction(std::function<bool(void)> function);
	
	/// <summary>
	/// Executes the function passed in the constructor
	/// and returns its result.
	/// </summary>
	/// <returns>
	///   The result of executing the function passed in the constructor
	/// </returns>
	bool ready() override;

private:
	std::function<bool(void)> function;
};