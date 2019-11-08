#include "TextObject.h"
#include "StringConverter.h"

TextObject::TextObject(FontProperties font, int zindex)
	:Object(zindex),
	 font(font),
	 maxWidth(0)
{
}

void TextObject::draw(IRenderer* renderer)
{
	if (valid() && visible())
	{
		font.setAlphaMod(getAlpha());
		font.drawLine(renderer, getPosition().x, getPosition().y, truncatedText);
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
	this->text = StringConverter::convertToUTF16(text);

	updateText();
}

void TextObject::setMaxWidth(int maxWidth, const std::string& ellipsis)
{
	this->maxWidth = maxWidth;
	this->ellipsis = StringConverter::convertToUTF16(ellipsis);

	updateText();
}

int TextObject::getWidth()
{
	int x, y;

	font.size(truncatedText, &x, &y);

	return x;
}

void TextObject::updateText()
{
	if (maxWidth > 0)
	{
		// Truncate text
		int end = text.size();
		int w, h;

		truncatedText = text;
		font.size(truncatedText, &w, &h);

		while (w > maxWidth && end > 0)
		{
			do
				--end;
			while (end > 0 && truncatedText[end-1] == L' ');

			truncatedText = truncatedText.substr(0, end) + ellipsis;
			font.size(truncatedText, &w, &h);
		}
	}
	else
	{
		truncatedText = text;
	}
}
