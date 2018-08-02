#pragma once

#include "Object.h"
#include "Config.h"
#include <string>
#include <vector>

/// <summary>
/// A list of buttons the player can click.
/// </summary>
/// <seealso cref="Object" />
class ButtonMenu : public Object
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="ButtonMenu"/> class.
	/// </summary>
	/// <param name="renderer">The renderer.</param>
	/// <param name="buttonBackground">The image to use as the background of the buttons.</param>
	/// <param name="zindex">The zindex.</param>
	/// <param name="position">The position of the menu area.</param>
	/// <param name="size">The size of the menu area.</param>
	/// <param name="separation">The separation between buttons.</param>
	/// <param name="useVerticalLayout">
	/// Whether or not the background image for the buttons contains
	/// the four states in a vertical layout.
	/// </param>
	ButtonMenu(
		class IRenderer* renderer,
		const std::string& buttonBackground,
		int zindex,
		const Vector2<int>& position,
		const Vector2<int>& size,
		const Vector2<int>& separation,
		bool useVerticalLayout = false
	);

	~ButtonMenu();
	
	/// <summary>
	/// Draws this object to the specified renderer context.
	/// </summary>
	/// <param name="renderer">The renderer.</param>
	void draw(class IRenderer* renderer) override;
	
	/// <summary>
	/// Updates this instance.
	/// </summary>
	/// <param name="elapsedSeconds">The elapsed seconds.</param>
	void update(float elapsedSeconds) override;
	
	/// <summary>
	/// Shows the menu, displaying a button for each choice.
	/// </summary>
	/// <param name="choices">The choices.</param>
	void show(const std::vector<std::string>& choices);
	
	/// <summary>
	/// Checks if the player has selected an option.
	/// </summary>
	/// <returns>
	/// <c>true</c> if the player has selected an option; otherwise, <c>false</c>.
	/// </returns>
	bool ready() const;
	
	/// <summary>
	/// Gets the index of the selected option.
	/// </summary>
	/// <returns>The index of the selected option.</returns>
	std::size_t getSelectedButton() const;

private:
	// Variables needed for button creation
	class IRenderer* renderer;
	std::string buttonBackground;
	bool useVerticalLayout;
	Vector2<int> separation;

	// Buttons for each menu choice
	std::vector<class ButtonObject*> buttons;

	// Button selected by the user
	std::size_t selectedButton;
	bool isReady;

	// Transition
	bool isInTransition;
	float transitionTime, transitionLength;
	float timePerButton, buttonDelay;
	float slope;

	void startTransition();
	void deleteButtons();
};