#pragma once

#include "Vector.h"
#include <SDL.h>
#include <functional>

/// <summary>
/// Handles mouse and keyboard input.
/// </summary>
class IInput
{
public:
	virtual ~IInput() {}

	// Raw input
	virtual bool isKeyDown(const SDL_Scancode& key) const = 0;
	virtual bool isMouseButtonDown(const Uint8& button) const = 0;
	virtual bool mouseButtonJustPressed(const Uint8& button) const = 0;
	virtual void getMouseCoordinates(int& outX, int& outY) = 0;

	// Actions	
	/// <summary>
	/// Whether or not to allow the player to skip
	/// blocking events with Ctrl or mouse click.
	/// </summary>
	/// <param name="allowSkipping">if set to <c>true</c> [allow skipping].</param>
	virtual void setAllowSkipping(bool allowSkipping) = 0;
	
	/// <summary>
	/// True if the user wants to skip whatever is on the
	/// screen by holding ctrl or pressing any button that
	/// will fire actionNext.
	/// </summary>
	virtual bool userWantsToSkip() const = 0;

	/// <summary>
	/// True if the user wants to read the next statement or
	/// skip a transition, e.g., by pressing LMB or enter.
	/// </summary>
	virtual bool actionNext() const = 0;
	
	/// <summary>
	/// True if the user wants to toggle fullscreen mode.
	/// </summary>
	virtual bool actionToggleFullscreen() const = 0;

 	/// <summary>
	/// Corrects mouse coordinates when the game is
	/// not being rendered at native resolution.
	/// </summary>
	/// <param name="scalingFactor">The scaling factor.</param>
	/// <param name="letterboxingOffset">The letterboxing offset.</param>
	virtual void correctMouseForWindowScaling(float scalingFactor, const Vector2<int>& letterboxingOffset) = 0;

	// Mouse	
	/// <summary>
	/// If mouse input is disabled, the user will not
	/// be able to interact with object that receive
	/// mouse input, such as buttons or clickable maps.
	/// <see cref="actionNext"/> will fire regardless
	/// of this setting.
	/// </summary>
	/// <param name="enabled">if set to <c>true</c> mouse input will be enabled.</param>
	virtual void setMouseInputEnabled(bool enabled) = 0;
	
	/// <summary>
	/// Disables the mouse input for objects with
	/// lower zindex than the one provided.
	/// </summary>
	/// <param name="zindex">The zindex.</param>
	virtual void disableMouseInputBelow(int zindex) = 0;
	
	/// <summary>
	/// Gets whether or not mouse input is enabled.
	/// </summary>
	/// <returns><c>true</c> if mouse input is enabled; otherwise, <c>false</c></returns>
	virtual bool getMouseInputEnabled() const = 0;
		
	/// <summary>
	/// Mark an object as being pointed by the user.
	/// This will be used to determine wich object
	/// the mouse is pointing to, if there are two
	/// overlapping objects.
	/// </summary>
	/// <param name="object">The object.</param>
	/// <param name="zindex">The zindex of the object.</param>
	virtual void setObjectPointedByUser(class IClickableObject* object, int zindex) = 0;
		
	/// <summary>
	/// Gets the object pointed by the mouse.
	/// If two objects overlap, the one with greater
	/// zindex will be returned.
	/// </summary>
	/// <returns>The object pointed by the user or <c>null</c> if there is no object.</returns>
	virtual class IClickableObject* getObjectPointedByUser() = 0;
	
	/// <summary>
	/// Sets the hardware cursor icon.
	/// </summary>
	/// <param name="cursor">The cursor.</param>
	virtual void setCursor(class Cursor* cursor) = 0;
	
	/// <summary>
	/// Sets a delegate function to be called when
	/// the user presses right mouse button.
	/// </summary>
	/// <param name="function">The function to call.</param>
	virtual void setOnRightClick(std::function<void(void)> function) = 0;
};