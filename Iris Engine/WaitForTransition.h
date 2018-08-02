#pragma once

#include "WaitCommand.h"

/// <summary>
/// Waits until the specified object is not
/// in a transition.
/// Used for blocking transitions.
/// </summary>
/// <seealso cref="WaitCommand" />
class WaitForTransition : public WaitCommand
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="WaitForTransition"/> class.
	/// </summary>
	/// <param name="object">The object.</param>
	WaitForTransition(class Object* object);
	
	/// <summary>
	/// Check if the object is not in a transition.
	/// </summary>
	/// <returns>
	///   <c>true</c> if the object is not in a transition; otherwise, <c>false</c>
	/// </returns>
	bool ready() override;

private:
	class Object* object;
};