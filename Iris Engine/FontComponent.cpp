#include "FontComponent.h"
#include "Locator.h"
#include "Config.h"
#include "IRenderer.h"
#include "ITexture.h"
#include "StringConverter.h"
#include <codecvt>

FontComponent::FontComponent(const FontProperties& fontProperties)
	:shadowDistance(fontProperties.shadowDistance),
	 alphaModulation(1.0f)
{
	font = TTF_OpenFont(fontProperties.fontFile.c_str(), fontProperties.fontSize);

	if (!font)
	{
		Locator::getLogger()->log(
			LogCategory::OBJECT,
			LogPriority::ERROR,
			u8"The font could not be loaded:\n" + std::string(TTF_GetError())
		);
	}

	this->fontColor = {
		fontProperties.fontColor.r,
		fontProperties.fontColor.g,
		fontProperties.fontColor.b,
		fontProperties.fontColor.a
	};

	this->shadowColor = {
		fontProperties.shadowColor.r,
		fontProperties.shadowColor.g,
		fontProperties.shadowColor.b,
		fontProperties.shadowColor.a
	};
}

FontComponent::~FontComponent()
{
	if (font)
		TTF_CloseFont(font);
}

int FontComponent::size(const std::u16string& line, int* outWidth, int* outHeight)
{
	return TTF_SizeUNICODE(font, (Uint16*)line.c_str(), outWidth, outHeight);
}

int FontComponent::size(const std::string& line, int* outWidth, int* outHeight)
{
	return size(StringConverter::convertToUTF16(line), outWidth, outHeight);
}

int FontComponent::getLineSkip()
{
	return TTF_FontLineSkip(font);
}

int FontComponent::getFontHeight()
{
	return TTF_FontHeight(font);
}

void FontComponent::drawLine(IRenderer* renderer, int x, int y, const std::u16string& line)
{
	if (shadowDistance)
		drawLine(renderer, x + shadowDistance, y + shadowDistance, line, shadowColor);

	drawLine(renderer, x, y, line, fontColor);
}

void FontComponent::drawLine(IRenderer* renderer, int x, int y, const std::string& line)
{
	drawLine(renderer, x, y, StringConverter::convertToUTF16(line));
}

void FontComponent::setColor(const Color& color)
{
	fontColor = {
		color.r,
		color.g,
		color.b,
		color.a
	};
}

void FontComponent::setShadowColor(const Color& color)
{
	shadowColor = {
		color.r,
		color.g,
		color.b,
		color.a
	};
}

void FontComponent::setAlphaMod(uint8_t alpha)
{
	alphaModulation = alpha / 255.0f;
}

void FontComponent::wordWrap(const std::u16string& text, int lineWidth, std::vector<std::u16string>& inOutLines)
{
	// Word wrap (this can probably be optimized)
	const std::u16string breakingChars = u" -\t\n";
	std::u16string line, word;

	std::size_t pos = 0;
	std::size_t wordEnd;
	char16_t breakChar;

	int width;
	int accumulatedWidth = 0;

	// Check if there is already text
	if (!inOutLines.empty())
	{
		// We want to append the new text to the previous one
		// Continue word wrapping from the last line
		line = inOutLines.back();
		inOutLines.pop_back();

		size(line, &accumulatedWidth, nullptr);
	}

	while (pos < text.length())
	{
		wordEnd = text.find_first_of(breakingChars, pos);

		if (wordEnd == std::u16string::npos)
			wordEnd = text.size() - 1;

		breakChar = text[wordEnd];

		if (breakChar != L'\n')
			++wordEnd;

		word = text.substr(pos, wordEnd - pos);
		size(word, &width, nullptr);

		if (accumulatedWidth + width <= lineWidth)
		{
			// The word fits in the line
			line += word;
			accumulatedWidth += width;
		}
		else
		{
			// Word doesn't fit in the line
			// Insert it in the next line unless it's already the first
			// word in the line.
			if (!line.empty())
			{
				inOutLines.push_back(line);
				line.clear();
			}

			if (width < lineWidth)
			{
				line += word;
				accumulatedWidth = width;
			}
			else
			{
				// The world is longer than an entire line
				inOutLines.push_back(std::u16string());
				splitInLinesNoWordWrap(word, lineWidth, inOutLines);
				line = inOutLines.back();
				inOutLines.pop_back();

				size(line, &accumulatedWidth, nullptr);
			}
		}

		pos = wordEnd;

		if (breakChar == L'\n')
		{
			++pos;

			// Line break
			inOutLines.push_back(line);
			line.clear();
			accumulatedWidth = 0;
		}
	}

	if (!line.empty())
		inOutLines.push_back(line);
}

void FontComponent::splitInLinesNoWordWrap(const std::u16string& text, int lineWidth, std::vector<std::u16string>& inOutLines)
{
	std::u16string line;
	std::size_t pos = 0;

	int width;

	const std::u16string openingQuotationMarks = u"「『（";
	const std::u16string closingQuotationMarks = u"」』）";
	const std::u16string japanesePunctuation = u"。、";
	const char16_t japaneseSpace = L'　';

	bool formatJapaneseText = Config::values().textWindow.formatJapaneseText;
	bool indent = formatJapaneseText && openingQuotationMarks.find(text.at(pos)) != std::u16string::npos;

	if (!inOutLines.empty())
	{
		// We want to append the new text to the previous one
		line = inOutLines.back();
		inOutLines.pop_back();

		if (!line.empty())
			indent = line.at(0) == japaneseSpace;
	}

	while (pos < text.length())
	{
		// We have to get the size of the entire line to account for kerning
		size(line + text.at(pos), &width, nullptr);

		if (indent && closingQuotationMarks.find(text.at(pos)) != std::u16string::npos)
			indent = false;

		if (width > lineWidth && (!formatJapaneseText || japanesePunctuation.find(text.at(pos)) == std::u16string::npos))
		{
			// The new character doesn't fit in the line: create new line
			inOutLines.push_back(line);
			line.clear();

			if (indent)
				line += u"　";
		}

		line += text.at(pos);
		++pos;
	}

	if (!line.empty())
		inOutLines.push_back(line);
}

void FontComponent::drawLine(IRenderer* renderer, int x, int y, const std::u16string& line, SDL_Color color)
{
	// Apply alpha modulation
	color.a *= alphaModulation;

	SDL_Surface* lineSurface = TTF_RenderUNICODE_Blended(font, (Uint16*)line.c_str(), color);

	if (lineSurface)
	{
		// Set position and size of the line
		SDL_Rect clipRect = lineSurface->clip_rect;
		Rect<float> rect;

		rect.x = x;
		rect.y = y;
		rect.w = clipRect.w;
		rect.h = clipRect.h;

		ITexture* lineTexture = renderer->createTexture(lineSurface);
		lineTexture->setBlendMode(BlendMode::FACTOR_ALPHA);
		SDL_FreeSurface(lineSurface);

		if (lineTexture)
		{
			lineTexture->setAlphaMod(color.a);
			renderer->copy(lineTexture, nullptr, &rect);
			delete lineTexture;
		}
		else
		{
			Locator::getLogger()->log(
				LogCategory::VIDEO,
				LogPriority::ERROR,
				u8"Error creating line shadow texture:\n" + std::string(SDL_GetError())
			);
		}
	}
	else
	{
		Locator::getLogger()->log(
			LogCategory::VIDEO,
			LogPriority::ERROR,
			u8"Error creating line shadow:\n" + std::string(TTF_GetError())
		);
	}
}
