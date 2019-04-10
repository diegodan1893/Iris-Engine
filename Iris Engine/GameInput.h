#pragma once

#include "IInput.h"

class IClickableObject;

/// <summary>
/// Handles mouse and keyboard input.
/// </summary>
/// <seealso cref="IInput" />
class GameInput : public IInput
{
private:
	struct InputState
	{
		bool mouseLeft;
		bool mouseMiddle;
		bool mouseRight;
		bool mouseWheelDown;
		bool enterKey;
		bool altEnterKeys;
	};

public:
	GameInput();
	~GameInput();

	// Update state
	void updateMouseButton(const Uint8& button, bool pressed);
	void updateMouseWheel(Sint32 y, Uint32 direction);
	void updateEnterKey(bool pressed);
	
	/// <summary>
	/// Consumes the state of the input.
	/// Needs to be called every frame.
	/// </summary>
	void consume();
	
	/// <summary>
	/// Handles the right mouse event.
	/// Needs to be called every frame before
	/// objects are updated.
	/// </summary>
	void handleRightMouseEvent();

	// Raw input
	bool isKeyDown(const SDL_Scancode& key) const override;
	bool isMouseButtonDown(const Uint8& button) const override;
	bool mouseButtonJustPressed(const Uint8& button) const override;
	void getMouseCoordinates(int& outX, int& outY) override;

	// Actions	
	/// <summary>
	/// Whether or not to allow the player to skip
	/// blocking events with Ctrl or mouse click.
	/// </summary>
	/// <param name="allowSkipping">if set to <c>true</c> [allow skipping].</param>
	void setAllowSkipping(bool allowSkipping) override;
	
	/// <summary>
	/// True if the user wants to skip whatever is on the
	/// screen by holding ctrl or pressing any button that
	/// will fire actionNext.
	/// </summary>
	bool userWantsToSkip() const override;
	
	/// <summary>
	/// True if the user wants to read the next statement or
	/// skip a transition, e.g., by pressing LMB or enter.
	/// </summary>
	bool actionNext() const override;
	
	/// <summary>
	/// True if the user wants to toggle fullscreen mode.
	/// </summary>
	bool actionToggleFullscreen() const override;

	// Fullscreen correction
	/// <summary>
	/// Corrects mouse coordinates for fullscreen.
	/// </summary>
	/// <param name="screenRes">The actual screen resolution.</param>
	/// <param name="gameRes">The game virtual resolution.</param>
	virtual void correctForFullscreen(const Vector2<int>& screenRes, const Vector2<int>& gameRes);
	
	/// <summary>
	/// Disables the fullscreen correction.
	/// </summary>
	virtual void disableFullscreenCorrection();

	// Mouse
	/// <summary>
	/// If mouse input is disabled, the user will not
	/// be able to interact with object that receive
	/// mouse input, such as buttons or clickable maps.
	/// <see cref="actionNext" /> will fire regardless
	/// of this setting.
	/// </summary>
	/// <param name="enabled">if set to <c>true</c> mouse input will be enabled.</param>
	void setMouseInputEnabled(bool enabled) override;

	/// <summary>
	/// Disables the mouse input for objects with
	/// lower zindex than the one provided.
	/// </summary>
	/// <param name="zindex">The zindex.</param>
	virtual void disableMouseInputBelow(int zindex);
	
	/// <summary>
	/// Gets whether or not mouse input is enabled.
	/// </summary>
	/// <returns>
	///   <c>true</c> if mouse input is enabled; otherwise, <c>false</c>
	/// </returns>
	bool getMouseInputEnabled() const override;
	
	/// <summary>
	/// Mark an object as being pointed by the user.
	/// This will be used to determine wich object
	/// the mouse is pointing to, if there are two
	/// overlapping objects.
	/// </summary>
	/// <param name="object">The object.</param>
	/// <param name="zindex">The zindex of the object.</param>
	void setObjectPointedByUser(IClickableObject* object, int zindex) override;
	
	/// <summary>
	/// Gets the object pointed by the mouse.
	/// If two objects overlap, the one with greater
	/// zindex will be returned.
	/// </summary>
	/// <returns>
	/// The object pointed by the user or <c>null</c> if there is no object.
	/// </returns>
	IClickableObject* getObjectPointedByUser() override;
		
	/// <summary>
	/// Sets the hardware cursor icon.
	/// </summary>
	/// <param name="cursor">The cursor.</param>
	void setCursor(class Cursor* cursor) override;
	
	/// <summary>
	/// Sets a delegate function to be called when
	/// the user presses right mouse button.
	/// </summary>
	/// <param name="function">The function to call.</param>
	void setOnRightClick(std::function<void(void)> function) override;

private:
	InputState inputBefore;
	InputState inputNow;
	bool allowSkipping;
	IClickableObject* objectPointedByUser;
	int objectZindex;
	bool mouseInputEnabled;
	int mouseInputMinZindex;

	// Fullscreen correction
	float zoom;
	Vector2<float> offset;

	// Mouse cursor
	struct SDL_Cursor* defaultCursor;

	// Right click delegate
	std::function<void(void)> onRightClick;
};