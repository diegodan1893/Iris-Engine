#include "ButtonMenu.h"
#include "ButtonObject.h"
#include "Locator.h"
#include "Sprite.h"
#include "IRenderer.h"
#include <cmath>

ButtonMenu::ButtonMenu(
	IRenderer* renderer,
	const std::string& buttonBackground,
	int zindex,
	const Vector2<int>& position,
	const Vector2<int>& size,
	const Vector2<int>& separation,
	bool useVerticalLayout
)
	:Object(zindex),
	 renderer(renderer),
	 buttonBackground(buttonBackground),
	 useVerticalLayout(useVerticalLayout),
	 separation(separation),
	 isInTransition(false)
{
	setPosition(position.x, position.y);
	setSize(size.x, size.y);

	//! @todo For now, use config values for transition, this should be generic
	timePerButton = Config::values().choices.showTransitionTime;
	buttonDelay = Config::values().choices.showTransitionDelay;
	slope = 255.0 / timePerButton;
}

ButtonMenu::~ButtonMenu()
{
	deleteButtons();
}

void ButtonMenu::draw(IRenderer* renderer)
{
	if (visible())
	{
		for (auto it = buttons.begin(); it != buttons.end(); ++it)
			(*it)->draw(renderer);
	}
}

void ButtonMenu::update(float elapsedSeconds)
{
	if (inFade())
		updateAlpha(elapsedSeconds);

	bool wasInTransition = isInTransition;
	float fadeStart, fadeEnd;

	if (isInTransition)
	{
		transitionTime += elapsedSeconds;
		
		if (transitionTime >= transitionLength)
			isInTransition = false;
	}

	if (visible())
	{
		for (std::size_t i = 0; i < buttons.size(); ++i)
		{
			buttons[i]->update(elapsedSeconds);
			
			if (wasInTransition)
			{
				if (!isInTransition)
				{
					// Transition has finished, enable button input
					buttons[i]->setDisableInput(false);
					buttons[i]->setAlpha(255);
				}
				else
				{
					// Show buttons with a fade
					fadeStart = buttonDelay * i;
					fadeEnd = fadeStart + timePerButton;

					if (transitionTime < fadeStart)
						buttons[i]->setAlpha(0);
					else if (transitionTime > fadeEnd)
						buttons[i]->setAlpha(255);
					else
						buttons[i]->setAlpha(slope * transitionTime - slope * fadeStart);
				}
			}
			else if (buttons[i]->shouldExecuteAction())
			{
				isReady = true;
				selectedButton = i;
			}
		}

		// If a button was selected, hide the menu
		if (isReady && !inFade())
		{
			for (auto it = buttons.begin(); it != buttons.end(); ++it)
			{
				// !@todo For now, hide buttons with a fade
				(*it)->setFrame(0);
				(*it)->startFadeOut(Config::values().choices.hideTransitionTime, true);
			}

			// !@todo For now, hide buttons with a fade
			startFadeOut(Config::values().choices.hideTransitionTime, true);
		}
	}
	else if (!buttons.empty())
	{
		deleteButtons();
	}
}

void ButtonMenu::show(const std::vector<std::string>& choices)
{
	isReady = false;

	// Make sure previous buttons are deallocated
	deleteButtons();

	// Get the size of the buttons in order to center them in the screen
	// This also avoids showing an error message for each button if the image can't be loaded
	Sprite* sprite = Locator::getCache()->getSprite(Config::values().paths.gui + buttonBackground);

	if (sprite)
	{
		Vector2<int> buttonSize = sprite->getTextureSize();
		if (useVerticalLayout)
			buttonSize.y /= 4;
		else
			buttonSize.x /= 4;

		// Calculate the size of the menu with all the butttons
		int menuWidth, menuHeight;
		menuWidth = std::abs((int)(separation.x * (choices.size() - 1))) + buttonSize.x;
		menuHeight = std::abs((int)(separation.y * (choices.size() - 1))) + buttonSize.y;

		// Center the menu inside the area defined in the config file
		int menuX = getSize().x / 2 - menuWidth / 2 + getPosition().x;
		int menuY = getSize().y / 2 - menuHeight / 2 + getPosition().y;

		// Create the buttons and place them in their position
		ButtonObject* button;

		for (std::size_t i = 0; i < choices.size(); ++i)
		{
			button = new ButtonObject(renderer, buttonBackground, getZindex(), choices[i], useVerticalLayout);
			
			//! @todo This doesn't work with negative numbers
			button->setPosition(std::round(menuX + separation.x * i), std::round(menuY + separation.y * i));
			button->setDisableInput(true);
			button->setVisible(true);

			buttons.push_back(button);;
		}

		setVisible(true);
		startTransition();
	}
}

bool ButtonMenu::ready() const
{
	return isReady;
}

std::size_t ButtonMenu::getSelectedButton() const
{
	return selectedButton;
}

void ButtonMenu::startTransition()
{
	isInTransition = true;
	transitionTime = 0;
	transitionLength = buttonDelay * (buttons.size() - 1) + timePerButton;
}

void ButtonMenu::deleteButtons()
{
	for (auto it = buttons.begin(); it != buttons.end(); ++it)
		delete *it;

	buttons.clear();
}
