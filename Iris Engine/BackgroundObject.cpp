#include "BackgroundObject.h"
#include "Config.h"
#include "Locator.h"
#include "Sprite.h"
#include "IRenderer.h"
#include "ITexture.h"
#include "ImageDissolveShader.h"

BackgroundObject::BackgroundObject(int zindex)
	:Object(zindex),
	 inImageDissolve(false)
{
	setPosition(0, 0);
	setOrigin(0, 0);
}

BackgroundObject::~BackgroundObject()
{
}

void BackgroundObject::draw(IRenderer* renderer)
{
	if (visible())
	{
		Sprite* sprite = Locator::getCache()->getSprite(backgroundPath);

		if (sprite)
		{
			ITexture* texture = sprite->getTexture();

			if (texture)
			{
				if (inDissolve())
				{
					if (inImageDissolve)
					{
						// Currently in the middle of an image dissolve
						ImageDissolveShader* imageDissolveShader = renderer->getImageDissolveShader();

						imageDissolveShader->bind();
						imageDissolveShader->setTransitionStep(getDissolveAlpha() / 255.0);
						renderer->copy(texture, nullptr, &getRect());
						imageDissolveShader->unbind();
					}
					else
					{
						// Currently in the middle of a dissolve
						Sprite* previousSprite = Locator::getCache()->getSprite(previousBackground);

						if (sprite)
						{
							ITexture* previousTexture = previousSprite->getTexture();

							if (previousTexture)
							{
								previousTexture->setAlphaMod(255);
								renderer->copy(previousTexture, nullptr, &getRect());
							}

							texture->setAlphaMod(getDissolveAlpha());
							renderer->copy(texture, nullptr, &getRect());
						}
						else
						{
							skipTransition();
						}
					}
				}
				else
				{
					texture->setAlphaMod(getAlpha());
					renderer->copy(texture, nullptr, &getRect());
				}
			}
		}
		else
		{
			// Hide object to avoid showing an error message every frame
			setVisible(false);
		}
	}
}

void BackgroundObject::update(float elapsedSeconds)
{
	if (inFade())
		updateAlpha(elapsedSeconds);

	if (inDissolve())
	{
		updateDissolveAlpha(elapsedSeconds);
	}
	else
	{
		if (inImageDissolve)
		{
			// Image dissolve just finished
			inImageDissolve = false;
		}
	}
}

void BackgroundObject::setBackground(const std::string& backgroundPath)
{
	// Reset properties
	setPosition(0, 0);
	setOrigin(0, 0);

	skipTransition();

	// Change sprite path
	this->backgroundPath = Config::values().paths.backgrounds + backgroundPath;

	// Set size and unhide object
	Sprite* sprite = Locator::getCache()->getSprite(this->backgroundPath);

	if (sprite)
	{
		setSize(sprite->getTextureSize().x, sprite->getTextureSize().y);
		setVisible(true);
	}
	else
	{
		setVisible(false);
	}
}

void BackgroundObject::startDissolveBackground(const std::string& newBackground, float time, bool canBeSkipped)
{
	previousBackground = backgroundPath;
	setBackground(newBackground);

	startDissolve(time, canBeSkipped);
}

void BackgroundObject::startImageDissolve(float time, const std::string& mask, bool canBeSkipped, IRenderer* renderer)
{
	std::string maskPath = Config::values().paths.transitions + mask;

	// Load transition image
	Sprite* sprite = Locator::getCache()->getSprite(maskPath);

	if (sprite)
	{
		// Bind transition image to shader
		ImageDissolveShader* imageDissolveShader = renderer->getImageDissolveShader();
		imageDissolveShader->bind();
		imageDissolveShader->setMaskImage(sprite->getTexture());
		imageDissolveShader->unbind();

		// Start image dissolve
		startDissolve(time, canBeSkipped);
		inImageDissolve = true;
	}
}
