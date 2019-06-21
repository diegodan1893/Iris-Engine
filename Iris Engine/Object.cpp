#include "Object.h"
#include "Locator.h"
#include <cmath>

Object::Object(int zindex)
	:zindex(zindex),
	 isVisible(false),
	 isValid(true),
	 origin(0, 0),
	 position(0, 0),
	 alpha(255),
	 isSpriteSheet(false),
	 movementInterpolator(nullptr)
{
	frameRect.x = frameRect.y = 0;
}

Object::~Object()
{
	if (movementInterpolator)
		delete movementInterpolator;
}

void Object::setOrigin(int x, int y)
{
	rect.x += origin.x;
	rect.y += origin.y;

	origin.x = x;
	origin.y = y;

	rect.x -= origin.x;
	rect.y -= origin.y;
}

void Object::setOrigin(const Vector2<int>& origin)
{
	setOrigin(origin.x, origin.y);
}

void Object::setPosition(float x, float y)
{
	position.x = x;
	position.y = y;

	rect.x = position.x - origin.x;
	rect.y = position.y - origin.y;
}

void Object::setPosition(const Vector2<float>& position)
{
	setPosition(position.x, position.y);
}

const Vector2<float>& Object::getPosition() const
{
	return position;
}

int Object::getZindex() const
{
	return zindex;
}

void Object::setVisible(bool visible)
{
	fade.skip();
	isVisible = visible;
	alpha = 255;
}

bool Object::visible() const
{
	return isVisible;
}

void Object::startFadeIn(float time, bool canBeSkipped)
{
	if (isValid)
	{
		setVisible(true);
		fade.start(time, false);
		this->canBeSkipped = canBeSkipped;
	}
}

void Object::startFadeOut(float time, bool canBeSkipped)
{
	if (isValid)
	{
		setVisible(true);
		fade.start(time, true);
		this->canBeSkipped = canBeSkipped;
	}
}

void Object::setAlpha(uint8_t alpha)
{
	fade.skip();

	this->alpha = alpha;
	isVisible = alpha > 0;
}

void Object::move(float x, float y, float time, bool canBeSkipped, Interpolator* interpolator)
{
	// Complete previous movement before starting a new one
	if (movementInterpolator)
	{
		if (movementInterpolator->inTransition())
			setPosition(targetPosition);

		delete movementInterpolator;
	}

	movementInterpolator = interpolator;

	startPosition = getPosition();
	targetPosition.x = x;
	targetPosition.y = y;

	movementInterpolator->start(time, false);

	this->canBeSkipped = canBeSkipped;
}

void Object::move(const Vector2<float> target, float time, bool canBeSkipped, Interpolator* interpolator)
{
	move(target.x, target.y, time, canBeSkipped, interpolator);
}

void Object::skipTransition()
{
	if (fade.inTransition())
	{
		fade.skip();
		alpha = std::round(fade.getStep() * 255);
		setVisible(alpha > 0);
	}

	if (dissolve.inTransition())
		dissolve.skip();

	skipMovement();
}

void Object::skipMovement()
{
	if (movementInterpolator && movementInterpolator->inTransition())
	{
		movementInterpolator->skip();
		setPosition(targetPosition);
	}
}

bool Object::inTransition() const
{
	return inFade() || inDissolve() || inMovement();
}

bool Object::isAnimatedSprite() const
{
	return isSpriteSheet;
}

void Object::defineSpriteSheet(int frameCount, int cols, int rows, int fps)
{
	defineSpriteSheetRaw(frameCount, cols, rows, fps);

	// Recalculate size of the render rect so that it only renders one frame
	setSize(rect.w, rect.h);
}

void Object::setFrame(int frameNumber)
{
	currentFrame = frameNumber;
	updateFrameRect(frameNumber);
}

int Object::getFrameCount() const
{
	return frameCount;
}

Rect<float>& Object::getRect()
{
	return rect;
}

void Object::setSize(int w, int h)
{
	if (isSpriteSheet)
	{
		// Render rect should only be the size of a frame as we only want to render one frame
		rect.w = w / cols;
		rect.h = h / rows;
	}
	else
	{
		rect.w = w;
		rect.h = h;
	}

	frameRect.w = rect.w;
	frameRect.h = rect.h;
}

Vector2<int> Object::getSize() const
{
	return Vector2<int>(rect.w, rect.h);
}

void Object::setValid(bool valid)
{
	isValid = valid;

	if (!isValid)
		skipTransition();
}

bool Object::valid() const
{
	return isValid;
}

bool Object::inFade() const
{
	return fade.inTransition();
}

bool Object::inDissolve() const
{
	return dissolve.inTransition();
}

bool Object::inMovement() const
{
	return movementInterpolator && movementInterpolator->inTransition();
}

Uint8 Object::getAlpha()
{
	return (Uint8)std::round(alpha);
}

void Object::updateAlpha(float elapsedSeconds)
{
	if (Locator::getInput()->userWantsToSkip() && canBeSkipped)
	{
		// User wants and is allowed to skip this transition
		skipTransition();
	}
	else
	{
		fade.update(elapsedSeconds);
		alpha = std::round(fade.getStep() * 255);
		
		isVisible = alpha > 0;
	}
}

float Object::getAlphaRaw()
{
	return alpha;
}

void Object::setAlphaRaw(float alpha)
{
	fade.skip();
	this->alpha = alpha;
}

void Object::startDissolve(float time, bool canBeSkipped)
{
	dissolve.start(time, false);
	this->canBeSkipped = canBeSkipped;
}

Uint8 Object::getDissolveAlpha()
{
	return std::round(dissolve.getStep() * 255);
}

void Object::updateDissolveAlpha(float elapsedSeconds)
{
	if (Locator::getInput()->userWantsToSkip() && canBeSkipped)
	{
		// User wants and is allowed to skip this transition
		skipTransition();
	}
	else
	{
		dissolve.update(elapsedSeconds);
	}
}

void Object::updateMovement(float elapsedSeconds)
{
	if (Locator::getInput()->userWantsToSkip() && canBeSkipped)
	{
		// User wants and is allowed to skip this transition
		skipTransition();
	}
	else
	{
		if (movementInterpolator)
		{
			movementInterpolator->update(elapsedSeconds);
			setPosition(lerp(startPosition, targetPosition, movementInterpolator->getStep()));
		}
	}
}

void Object::defineSpriteSheetRaw(int frameCount, int cols, int rows, int fps)
{
	// Avoid division by zero
	if (frameCount > 0 && cols > 0 && rows > 0 && fps >= 0)
	{
		isSpriteSheet = true;
		this->frameCount = frameCount;
		this->cols = cols;
		this->rows = rows;
		this->fps = fps;
		currentFrame = 0;
	}
}

Rect<float>& Object::getFrameRect()
{
	return frameRect;
}

void Object::updateSpriteAnimation(float elapsedSeconds)
{
	currentFrame += fps * elapsedSeconds;

	if (currentFrame >= frameCount)
	{
		currentFrame -= frameCount;

		if (currentFrame > frameCount)
			currentFrame = 0;
	}

	updateFrameRect((int)currentFrame);
}

void Object::updateFrameRect(int frameNumber)
{
	int frameCol = frameNumber % cols;
	int frameRow = frameNumber / cols;

	frameRect.x = frameCol * frameRect.w;
	frameRect.y = frameRow * frameRect.h;
}
