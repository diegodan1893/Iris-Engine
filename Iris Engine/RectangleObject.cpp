#include "RectangleObject.h"
#include "IRenderer.h"

RectangleObject::RectangleObject(int zindex)
	:Object(zindex),
	 color(0, 0, 0, 255)
{
	setSize(0, 0);
}

RectangleObject::~RectangleObject()
{
}

void RectangleObject::draw(IRenderer* renderer)
{
	if (valid() && visible())
	{
		Color finalColor = color;

		finalColor.a = getAlpha() / 255.0f * color.a;

		renderer->rectangle(getRect(), finalColor);
	}
}

void RectangleObject::update(float elapsedSeconds)
{
	if (inFade())
		updateAlpha(elapsedSeconds);

	if (inMovement())
		updateMovement(elapsedSeconds);
}

void RectangleObject::setRectangleSize(int width, int height)
{
	setSize(width, height);
}

void RectangleObject::setColor(Color color)
{
	this->color = color;
}
