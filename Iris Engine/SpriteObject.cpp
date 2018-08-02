#include "SpriteObject.h"
#include "Config.h"
#include "Locator.h"
#include "Sprite.h"
#include "IRenderer.h"
#include "ITexture.h"

SpriteObject::SpriteObject(const std::string& file, int zindex, Vector2<float> position, Vector2<int> origin)
	:Object(zindex),
	 sizeWasSet(false)
{
	setSpritePath(Config::values().paths.sprites + file);
	setPosition(position);
	setOrigin(origin);
}

SpriteObject::SpriteObject(const std::string& file, const std::string& path, int zindex, Vector2<float> position, Vector2<int> origin)
	:Object(zindex),
	 sizeWasSet(false)
{
	setSpritePath(path + file);
	setPosition(position);
	setOrigin(origin);
}

SpriteObject::~SpriteObject()
{
}

void SpriteObject::draw(IRenderer* renderer)
{
	if (valid() && visible())
	{
		Sprite* sprite = Locator::getCache()->getSprite(spritePath);

		if (sprite)
		{
			if (!sizeWasSet)
			{
				setSize(sprite->getTextureSize().x, sprite->getTextureSize().y);
				sizeWasSet = true;
			}

			ITexture* texture = sprite->getTexture();

			if (texture)
			{
				texture->setAlphaMod(getAlpha());
				renderer->copy(texture, &getFrameRect(), &getRect());
			}
		}
		else
		{
			// Avoid showing an error message every frame
			setValid(false);
		}
	}
}

void SpriteObject::update(float elapsedSeconds)
{
	if (inFade())
		updateAlpha(elapsedSeconds);

	if (isAnimatedSprite())
		updateSpriteAnimation(elapsedSeconds);

	if (inMovement())
		updateMovement(elapsedSeconds);
}

bool SpriteObject::getSizeWasSet() const
{
	return sizeWasSet;
}

void SpriteObject::setSizeWasSet(bool sizeWasSet)
{
	this->sizeWasSet = sizeWasSet;
}

const std::string& SpriteObject::getSpritePath() const
{
	return spritePath;
}

void SpriteObject::setSpritePath(const std::string& file)
{
	spritePath = file;

	// Precache if necessary
	if (Config::values().cache.allowPrecaching)
	{
		Sprite* sprite = Locator::getCache()->getSprite(spritePath);

		if (sprite)
		{
			setSize(sprite->getTextureSize().x, sprite->getTextureSize().y);
			sizeWasSet = true;
		}
		else
		{
			setValid(false);
		}
	}
}
