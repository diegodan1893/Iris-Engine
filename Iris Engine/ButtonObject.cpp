#include "ButtonObject.h"
#include "FontComponent.h"
#include "Locator.h"
#include "Sprite.h"
#include "IRenderer.h"
#include "ITexture.h"

ButtonObject::ButtonObject(const std::string& file, int zindex, bool useVerticalLayout)
	:SpriteObject(file, Config::values().paths.gui, zindex),
	 buttonTexture(nullptr),
	 state(ButtonState::UP),
	 previousState(ButtonState::UP),
	 shouldExecute(false),
	 disableInput(false)
{
	if (useVerticalLayout)
		defineSpriteSheet(4, 1, 4, 0);
	else
		defineSpriteSheet(4, 4, 1, 0);
}

ButtonObject::ButtonObject(
	IRenderer* renderer,
	const std::string& file,
	int zindex,
	const std::string& text,
	bool useVerticalLayout,
	const FontProperties& fontProperties,
	const Color& disabledFontColor,
	const Color& disabledShadowColor
)
	:SpriteObject(file, Config::values().paths.gui, zindex),
	 state(ButtonState::UP),
	 previousState(ButtonState::UP),
	 shouldExecute(false),
	 disableInput(false)
{
	// Prerender text into button texture
	Sprite* sprite = Locator::getCache()->getSprite(getSpritePath());

	if (sprite)
	{
		setSize(sprite->getTextureSize().x, sprite->getTextureSize().y);
		setSizeWasSet(true);

		buttonTexture = renderer->createTexture(TextureFormat::RGBA8, TextureAccess::TARGET, getRect().w, getRect().h);

		if (buttonTexture)
		{
			buttonTexture->setBlendMode(BlendMode::BLEND);

			// Start rendering to texture
			renderer->setRenderTarget(buttonTexture);

			ITexture* buttonBackground = sprite->getTexture();

			if (buttonBackground)
			{
				buttonBackground->setBlendMode(BlendMode::NONE);
				renderer->copy(buttonBackground, nullptr, &getRect());
				buttonBackground->setBlendMode(BlendMode::BLEND);
			}

			if (useVerticalLayout)
				defineSpriteSheet(4, 1, 4, 0);
			else
				defineSpriteSheet(4, 4, 1, 0);

			// Draw text
			FontComponent font(fontProperties);

			Rect<float> rect = getFrameRect();;
			int textWidth, textHeight;
			int textX, textY;

			font.size(text, &textWidth, &textHeight);

			textX = rect.w / 2 - textWidth / 2;
			textY = rect.h / 2 - textHeight / 2;

			for (int i = 0; i < 4; ++i)
			{
				setFrame(i);
				rect = getFrameRect();

				if (i == 3)
				{
					font.setColor(disabledFontColor);
					font.setShadowColor(disabledShadowColor);
				}

				font.drawLine(renderer, rect.x + textX, rect.y + textY, text);
			}

			setFrame(0);

			// Stop rendering to texture
			renderer->setRenderTarget(nullptr);
		}
		else
		{
			// Button texture could not be created
			Locator::getLogger()->log(
				LogCategory::OBJECT,
				LogPriority::ERROR,
				u8"Button texture could not be created:\n" + std::string(SDL_GetError())
			);
		}
	}
	else
	{
		setValid(false);
	}
}

ButtonObject::~ButtonObject()
{
	if (buttonTexture)
		delete buttonTexture;
}

void ButtonObject::draw(IRenderer* renderer)
{
	//! @todo This is a hack
	previousState = state;

	// Draw code
	if (buttonTexture)
	{
		// Draw using prerendered texture
		if (visible() && valid())
		{
			buttonTexture->setAlphaMod(getAlpha());
			renderer->copy(buttonTexture, &getFrameRect(), &getRect());
		}
	}
	else
	{
		// Draw as any SpriteObject
		SpriteObject::draw(renderer);
	}
}

void ButtonObject::update(float elapsedSeconds)
{
	SpriteObject::update(elapsedSeconds);

	if (visible() && state != ButtonState::DISABLED && !inTransition() && !disableInput)
	{
		setButtonState(ButtonState::UP);

		Rect<float> rect = getRect();
		int mouseX, mouseY;
		Locator::getInput()->getMouseCoordinates(mouseX, mouseY);

		bool mouseIsOverX = mouseX > rect.x && mouseX < rect.x + rect.w;
		bool mouseIsOverY = mouseY > rect.y && mouseY < rect.y + rect.h;

		if (mouseIsOverX && mouseIsOverY)
		{
			Locator::getInput()->setObjectPointedByUser(this, getZindex());
		}
		else
		{
			if (previousState == ButtonState::HOVER || previousState == ButtonState::DOWN)
			{
				if (onMouseExit)
					onMouseExit();
			}
		}
	}
}

void ButtonObject::setEnabled(bool enabled)
{
	if (!enabled)
		setButtonState(ButtonState::DISABLED);
	else
		setButtonState(ButtonState::UP);
}

bool ButtonObject::shouldExecuteAction()
{
	return shouldExecute;
}

void ButtonObject::setDisableInput(bool disableInput)
{
	this->disableInput = disableInput;
}

void ButtonObject::setOnMouseEnter(std::function<void(void)> function)
{
	onMouseEnter = function;
}

void ButtonObject::setOnMouseExit(std::function<void(void)> function)
{
	onMouseExit = function;
}

void ButtonObject::setOnClick(std::function<void(void)> function)
{
	onClick = function;
}

void ButtonObject::handleMouseInput()
{
	if (state != ButtonState::DISABLED)
	{
		bool mouseJustPressed = Locator::getInput()->mouseButtonJustPressed(SDL_BUTTON_LEFT);
		bool mousePressed = Locator::getInput()->isMouseButtonDown(SDL_BUTTON_LEFT);

		switch (previousState)
		{
		case ButtonObject::ButtonState::UP:
			setButtonState(ButtonState::HOVER);
			Locator::getAudio()->playSound(Config::values().sounds.buttonHoverSound);

			if (onMouseEnter)
				onMouseEnter();

			break;

		case ButtonObject::ButtonState::HOVER:
			if (mouseJustPressed)
				setButtonState(ButtonState::DOWN);
			else
				setButtonState(ButtonState::HOVER);

			break;

		case ButtonObject::ButtonState::DOWN:
			if (!mousePressed)
			{
				setButtonState(ButtonState::HOVER);
				shouldExecute = true;
				Locator::getAudio()->playSound(Config::values().sounds.buttonClickSound);

				if (onClick)
					onClick();
			}
			else
			{
				setButtonState(ButtonState::DOWN);
			}

			break;
		}
	}
}

void ButtonObject::setAlpha(float alpha)
{
	setAlphaRaw(alpha);
}

void ButtonObject::setButtonState(ButtonState newState)
{
	state = newState;

	switch (state)
	{
	case ButtonObject::ButtonState::UP:
		setFrame(0);
		break;

	case ButtonObject::ButtonState::HOVER:
		setFrame(1);
		break;

	case ButtonObject::ButtonState::DOWN:
		setFrame(2);
		break;

	case ButtonObject::ButtonState::DISABLED:
		setFrame(3);
		break;

	default:
		break;
	}
}
