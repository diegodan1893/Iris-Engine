#pragma once

#include "WaitCommand.h"

/// <summary>
/// Waits until an object has the specified visibility.
/// </summary>
/// <seealso cref="WaitCommand" />
class WaitForVisible : public WaitCommand
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="WaitForVisible"/> class
	/// that waits until the object has the specified visibility.
	/// </summary>
	/// <param name="object">The object.</param>
	/// <param name="visible">
	///		if set to <c>true</c>, wait until the object is visible; otherwise, wait until the object not invisible.
	/// </param>
	WaitForVisible(class Object* object, bool visible);
	
	/// <summary>
	/// Check if the object has the specified visibility.
	/// </summary>
	/// <returns>
	///   <c>true</c> if the condition has been met; otherwise, <c>false</c>
	/// </returns>
	bool ready() override;

private:
	class Object* object;
	bool visible;
};