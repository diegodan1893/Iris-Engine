#include "GameInput.h"
#include "Object.h"
#include "Cursor.h"
#include <cmath>

GameInput::GameInput()
	:allowSkipping(true),
	 objectPointedByUser(nullptr),
	 defaultCursor(nullptr),
	 mouseInputEnabled(true),
	 mouseInputMinZindex(INT_MIN)
{
	inputNow.mouseLeft = inputNow.mouseMiddle = inputNow.mouseRight = false;
	inputNow.mouseWheelDown = inputNow.enterKey = inputNow.altEnterKeys = false;
	inputBefore = inputNow;

	disableFullscreenCorrection();
}

GameInput::~GameInput()
{
	if (defaultCursor)
		SDL_FreeCursor(defaultCursor);
}

void GameInput::updateMouseButton(const Uint8& button, bool pressed)
{
	switch (button)
	{
	case SDL_BUTTON_LEFT:
		inputBefore.mouseLeft = inputNow.mouseLeft;
		inputNow.mouseLeft = pressed;
		break;

	case SDL_BUTTON_MIDDLE:
		inputBefore.mouseMiddle = inputNow.mouseMiddle;
		inputNow.mouseMiddle = pressed;
		break;

	case SDL_BUTTON_RIGHT:
		inputBefore.mouseRight = inputNow.mouseRight;
		inputNow.mouseRight = pressed;
		break;
	}
}

void GameInput::updateMouseWheel(Sint32 y, Uint32 direction)
{
	inputBefore.mouseWheelDown = inputNow.mouseWheelDown;

	// The direction of the movement can be flipped in some systems
	if (direction == SDL_MOUSEWHEEL_FLIPPED)
		y *= -1;

	// Negative 'y' means scrolling down
	inputNow.mouseWheelDown = y < 0;
}

void GameInput::updateEnterKey(bool pressed)
{
	if (isKeyDown(SDL_SCANCODE_LALT) && pressed)
	{
		inputBefore.altEnterKeys = inputNow.altEnterKeys;
		inputNow.altEnterKeys = pressed;
	}
	else
	{
		inputBefore.enterKey = inputNow.enterKey;
		inputNow.enterKey = pressed;
		inputNow.altEnterKeys = false;
	}
}

void GameInput::consume()
{
	// Consume input
	inputBefore = inputNow;

	// Mouse wheel events are not fired when the user stops scrolling
	// so we need to reset the state manually
	inputNow.mouseWheelDown = false;

	objectPointedByUser = nullptr;
}

void GameInput::handleRightMouseEvent()
{
	// Fire right click event if necessary
	if (onRightClick && mouseInputEnabled && mouseButtonJustPressed(SDL_BUTTON_RIGHT))
		onRightClick();
}

bool GameInput::isKeyDown(const SDL_Scancode& key) const
{
	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[key])
		return true;
	else
		return false;
}

bool GameInput::isMouseButtonDown(const Uint8& button) const
{
	bool buttonState = false;

	switch (button)
	{
	case SDL_BUTTON_LEFT:
		buttonState = inputNow.mouseLeft;
		break;

	case SDL_BUTTON_MIDDLE:
		buttonState = inputNow.mouseMiddle;
		break;

	case SDL_BUTTON_RIGHT:
		buttonState = inputNow.mouseRight;
		break;
	}

	return buttonState;
}

bool GameInput::mouseButtonJustPressed(const Uint8& button) const
{
	bool buttonState = false;

	switch (button)
	{
	case SDL_BUTTON_LEFT:
		buttonState = inputNow.mouseLeft && !inputBefore.mouseLeft;
		break;

	case SDL_BUTTON_MIDDLE:
		buttonState = inputNow.mouseMiddle && !inputBefore.mouseMiddle;
		break;

	case SDL_BUTTON_RIGHT:
		buttonState = inputNow.mouseRight && !inputBefore.mouseRight;
		break;
	}

	return buttonState;
}

void GameInput::getMouseCoordinates(int& outX, int& outY)
{
	SDL_GetMouseState(&outX, &outY);

	outX = std::round((outX - offset.x) / zoom);
	outY = std::round((outY - offset.y) / zoom);
}

void GameInput::setAllowSkipping(bool allowSkipping)
{
	this->allowSkipping = allowSkipping;
}

bool GameInput::userWantsToSkip() const
{
	bool userIsTryingToSkip = actionNext()
		|| isKeyDown(SDL_SCANCODE_LCTRL)
		|| isKeyDown(SDL_SCANCODE_RCTRL);

	return allowSkipping && userIsTryingToSkip;
}

bool GameInput::actionNext() const
{
	// True if the user just pressed left mouse button, pressed enter or scrolled down

	return mouseButtonJustPressed(SDL_BUTTON_LEFT)
		|| (inputNow.enterKey && !inputBefore.enterKey)
		|| (inputNow.mouseWheelDown && !inputBefore.mouseWheelDown);
}

bool GameInput::actionToggleFullscreen() const
{
	return inputNow.altEnterKeys && !inputBefore.altEnterKeys;
}

void GameInput::correctForFullscreen(const Vector2<int>& screenRes, const Vector2<int>& gameRes)
{
	if (gameRes.x > gameRes.y)
	{
		zoom = (float)screenRes.x / gameRes.x;
		offset.y = std::abs(screenRes.y - gameRes.y * zoom) / 2.0f;
	}
	else
	{
		zoom = (float)screenRes.y / gameRes.y;
		offset.x = std::abs(screenRes.x - gameRes.x * zoom) / 2.0f;
	}
}

void GameInput::disableFullscreenCorrection()
{
	zoom = 1;
	offset.x = offset.y = 0;
}

void GameInput::setMouseInputEnabled(bool enabled)
{
	mouseInputEnabled = enabled;
}

void GameInput::disableMouseInputBelow(int zindex)
{
	mouseInputMinZindex = zindex;
}

bool GameInput::getMouseInputEnabled() const
{
	return mouseInputEnabled;
}

void GameInput::setObjectPointedByUser(IClickableObject* object, int zindex)
{
	if (zindex >= mouseInputMinZindex)
	{
		if (!objectPointedByUser)
		{
			objectPointedByUser = object;
			objectZindex = zindex;
		}
		else
		{
			if (objectZindex <= zindex)
			{
				objectPointedByUser = object;
				objectZindex = zindex;
			}
		}
	}
}

IClickableObject* GameInput::getObjectPointedByUser()
{
	if (mouseInputEnabled)
		return objectPointedByUser;
	else
		return nullptr;
}

void GameInput::setCursor(Cursor* cursor)
{
	if (cursor)
	{
		SDL_SetCursor(cursor->getCursor());
	}
	else
	{
		if (!defaultCursor)
			defaultCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);

		SDL_SetCursor(defaultCursor);
	}
}

void GameInput::setOnRightClick(std::function<void(void)> function)
{
	onRightClick = function;
}
