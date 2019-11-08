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
