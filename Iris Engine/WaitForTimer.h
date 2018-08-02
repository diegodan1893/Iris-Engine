#pragma once

#include "WaitCommand.h"

/// <summary>
/// Waits until the current timer has expired.
/// Used for sleep commands and such.
/// </summary>
/// <seealso cref="WaitCommand" />
class WaitForTimer : public WaitCommand
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="WaitForTimer"/> class.
	/// </summary>
	/// <param name="gameObjectManager">The game object manager.</param>
	WaitForTimer(class GameObjectManager* gameObjectManager);
	
	/// <summary>
	/// Check whether or not the time in the current timer
	/// has passed.
	/// </summary>
	/// <returns>
	///   <c>true</c> if the timer has finished; otherwise, <c>false</c>
	/// </returns>
	bool ready() override;

private:
	class GameObjectManager* gameObjectManager;
};