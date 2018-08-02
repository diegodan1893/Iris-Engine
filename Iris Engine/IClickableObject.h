#pragma once

/// <summary>
/// Interface that allow objects that implement it
/// to receive mouse input only when there are no
/// other objects on top of them.
/// </summary>
class IClickableObject
{
public:
	virtual ~IClickableObject() {}
	
	/// <summary>
	/// Called when the object is pointed by the player
	/// and is on top of any other object that can
	/// accept mouse input.
	/// The object must register itself with
	/// IInput::setObjectPointedByUser for this to
	/// work.
	/// </summary>
	virtual void handleMouseInput() = 0;
};