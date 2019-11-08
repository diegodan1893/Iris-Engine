#include "TextObject.h"

TextObject::TextObject(FontProperties font, int zindex)
	:Object(zindex),
	 font(font)
{
}

void TextObject::draw(IRenderer* renderer)
{
	if (valid() && visible())
	{
		font.setAlphaMod(getAlpha());
		font.drawLine(renderer, getPosition().x, getPosition().y, text);
	}
}

void TextObject::update(float elapsedSeconds)
{
	if (inFade())
		updateAlpha(elapsedSeconds);

	if (inMovement())
		updateMovement(elapsedSeconds);
}

void TextObject::setText(const std::string& text)
{
	this->text = text;
}

int TextObject::getWidth()
{
	int x, y;

	font.size(text, &x, &y);

	return x;
}
