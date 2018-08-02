#pragma once

#include "SpriteObject.h"
#include "IClickableObject.h"
#include "Config.h"
#include <functional>

/// <summary>
/// A button that the user can click.
/// </summary>
/// <seealso cref="SpriteObject" />
/// <seealso cref="IClickableObject" />
class ButtonObject : public SpriteObject, IClickableObject
{
private:	
	/// <summary>
	/// Possible states of a button.
	/// </summary>
	enum class ButtonState
	{
		UP,
		HOVER,
		DOWN,
		DISABLED
	};

public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="ButtonObject"/> class.
	/// </summary>
	/// <param name="file">The path to the image to use as the background.</param>
	/// <param name="zindex">The zindex.</param>
	/// <param name="useVerticalLayout">
	/// Whether or not the background image for the button contains
	/// the backgrounds for the four states (up, hover...) in a vertical layout.
	/// </param>
	ButtonObject(
		const std::string& file,
		int zindex,
		bool useVerticalLayout = false
	);
	
	/// <summary>
	/// Initializes a new instance of the <see cref="ButtonObject"/> class.
	/// </summary>
	/// <param name="renderer">The renderer.</param>
	/// <param name="file">The path to the image to use as the background.</param>
	/// <param name="zindex">The zindex.</param>
	/// <param name="text">The text of the button.</param>
	/// <param name="useVerticalLayout">
	/// Whether or not the background image for the button contains
	/// the backgrounds for the four states (up, hover...) in a vertical layout.
	/// </param>
	/// <param name="fontProperties">
	/// The properties of the font to use when drawing the text of the button.
	/// </param>
	/// <param name="disabledFontColor">
	/// The main color of the text when the button is disabled.
	/// </param>
	/// <param name="disabledShadowColor">
	/// The color of the shadow of the text when the button is disabled.
	/// </param>
	ButtonObject(
		class IRenderer* renderer,
		const std::string& file,
		int zindex,
		const std::string& text,
		bool useVerticalLayout = false,
		const FontProperties& fontProperties = Config::values().textWindow.fontProperties,
		const Color& disabledFontColor = Color(255, 255, 255, 150),
		const Color& disabledShadowColor = Color(0, 0, 0, 50)
	);

	virtual ~ButtonObject();
	
	/// <summary>
	/// Draws this object to the specified renderer context.
	/// </summary>
	/// <param name="renderer">The renderer.</param>
	virtual void draw(class IRenderer* renderer) override;

	/// <summary>
	/// Updates this instance.
	/// </summary>
	/// <param name="elapsedSeconds">The elapsed seconds.</param>
	virtual void update(float elapsedSeconds) override;
	
	/// <summary>
	/// Sets whether or not the button should be disabled.
	/// </summary>
	/// <param name="enabled">if set to <c>false</c> the button will be disabled.</param>
	void setEnabled(bool enabled);
	
	/// <summary>
	/// Checks if the player has clicked on this button.
	/// </summary>
	/// <returns>
	/// <c>true</c> if the player has clicked the button; otherwise, <c>false</c>.
	/// </returns>
	bool shouldExecuteAction();
	
	/// <summary>
	/// Makes the button not clickable without setting its state to <c>disabled</c>.
	/// </summary>
	/// <param name="disableInput">
	/// if set to <c>true</c> the button will not accept mouse input of any kind.
	/// </param>
	void setDisableInput(bool disableInput);

	// Delegates	
	/// <summary>
	/// Sets a delegate function to be called when the mouse enters
	/// the button.
	/// </summary>
	/// <param name="function">The function to call.</param>
	void setOnMouseEnter(std::function<void(void)> function);

	/// <summary>
	/// Sets a delegate function to be called when the mouse leaves
	/// the button.
	/// </summary>
	/// <param name="function">The function to call.</param>
	void setOnMouseExit(std::function<void(void)> function);

	/// <summary>
	/// Sets a delegate function to be called when the user clicks
	/// the button.
	/// </summary>
	/// <param name="function">The function to call.</param>
	void setOnClick(std::function<void(void)> function);
	
	/// <summary>
	/// Updates the state of the button and performs the necessary
	/// actions based on mouse input.
	/// This function assumes that there is no other objects on top
	/// of the button.
	/// </summary>
	void handleMouseInput() override;
	
	/// <summary>
	/// Sets the alpha transparency of the button.
	/// </summary>
	/// <param name="alpha">The alpha transparency, a number between 0 and 255.</param>
	void setAlpha(float alpha);

private:
	class ITexture* buttonTexture;
	ButtonState state, previousState;
	bool shouldExecute;
	bool disableInput;

	// Delegates
	std::function<void(void)> onMouseEnter;
	std::function<void(void)> onMouseExit;
	std::function<void(void)> onClick;

	void setButtonState(ButtonState newState);
};