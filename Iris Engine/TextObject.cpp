#include "TextObject.h"
#include "StringConverter.h"
#include <algorithm>

TextObject::TextObject(FontProperties font, int zindex)
	:Object(zindex),
	 font(font),
	 ellipsis(u"..."),
	 maxWidth(0),
	 maxHeight(0),
	 lineSpacing(0)
{
}

void TextObject::draw(IRenderer* renderer)
{
	if (valid() && visible())
	{
		font.setAlphaMod(getAlpha());

		if (lines.empty() && !text.empty())
		{
			// Text is not truncated, draw the text string
			font.drawLine(renderer, getPosition().x, getPosition().y, text);
		}
		else
		{
			// Text is truncated, draw the word-wrapped text
			int y = getPosition().y;

			for (int i = 0; i < lines.size(); ++i)
			{
				if (!lines[i].empty())
					font.drawLine(renderer, getPosition().x, y, lines[i]);
				
				y += font.getLineSkip() + lineSpacing;
			}
		}
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

void TextObject::setMaxSize(int maxWidth, int maxHeight)
{
	this->maxWidth = maxWidth;
	this->maxHeight = maxHeight;

	updateText();
}

void TextObject::setEllipsis(const std::string & ellipsis)
{
	this->ellipsis = StringConverter::convertToUTF16(ellipsis);

	updateText();
}

void TextObject::setSpacing(int spacing)
{
	this->lineSpacing = spacing;

	updateText();
}

Vector2<int> TextObject::getCurrentTextSize()
{
	Vector2<int> size(0, 0);

	if (lines.empty() && !text.empty())
	{
		font.size(text, &size.x, &size.y);
	}
	else
	{
		int w, h;

		// Return the width of the longest line
		for (int i = 0; i < lines.size(); ++i)
		{
			font.size(lines[i], &w, &h);

			if (w > size.x)
				size.x = w;
		}

		size.y = (font.getLineSkip() + lineSpacing) * lines.size();
	}

	return size;
}

void TextObject::updateText()
{
	bool addEllipsis = false;
	int maxLines = 0;

	// Calculate number of lines
	if (maxHeight > 0)
	{
		maxLines = std::max(maxHeight / (font.getLineSkip() + lineSpacing), 1);
	}

	// Clear previous text
	lines.clear();

	if (maxWidth > 0)
	{
		// There is a limit to the width, word wrap
		font.wordWrap(text, maxWidth, lines);

		// Make sure we don't exceed the max height
		if (maxLines > 0 && lines.size() > maxLines)
		{
			// Concatenate last two lines
			lines[maxLines - 1] += lines[maxLines];

			lines.resize(maxLines);
			addEllipsis = true;
		}

		if (addEllipsis)
		{
			// Truncate last line
			std::u16string& lastLine = lines.back();
			int end = lastLine.size();
			int w, h;

			font.size(lastLine, &w, &h);

			do
			{
				while (end > 0 && lastLine[end - 1] == L' ')
					--end;

				lastLine = lastLine.substr(0, end) + ellipsis;
				font.size(lastLine, &w, &h);
				--end;
			} while (w > maxWidth && end > 0);
		}
	}
}
