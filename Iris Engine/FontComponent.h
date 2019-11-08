#pragma once

#include "FontProperties.h"
#include <SDL_ttf.h>

/// <summary>
/// Component that can render text to a
/// render target.
/// </summary>
class FontComponent
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="FontComponent"/> class.
	/// </summary>
	/// <param name="fontProperties">The font properties.</param>
	FontComponent(const FontProperties& fontProperties);

	~FontComponent();
	
	/// <summary>
	/// Calculates the size in pixels of the specified text.
	/// </summary>
	/// <param name="line">The line of text in UTF-16.</param>
	/// <param name="outWidth">Filled with the width in pixels. Can be <c>null</c>.</param>
	/// <param name="outHeight">Filled with the height in pixels. Can be <c>null</c>.</param>
	/// <returns>0 if there were no errors.</returns>
	int size(const std::u16string& line, int* outWidth, int* outHeight);

	/// <summary>
	/// Calculates the size in pixels of the specified text.
	/// </summary>
	/// <param name="line">The line of text in UTF-8.</param>
	/// <param name="outWidth">Filled with the width in pixels. Can be <c>null</c>.</param>
	/// <param name="outHeight">Filled with the height in pixels. Can be <c>null</c>.</param>
	/// <returns>0 if there were no errors.</returns>
	int size(const std::string& line, int* outWidth, int* outHeight);
	
	/// <summary>
	/// Gets the recommended line spacing for the font.
	/// </summary>
	/// <returns></returns>
	int getLineSkip();
	
	/// <summary>
	/// Gets the maximum pixel height of all the glyphs of the font.
	/// </summary>
	/// <returns></returns>
	int getFontHeight();
	
	/// <summary>
	/// Draws the line.
	/// </summary>
	/// <param name="renderer">The renderer.</param>
	/// <param name="x">The x position of the text.</param>
	/// <param name="y">The y position of the text.</param>
	/// <param name="line">The line to render.</param>
	void drawLine(class IRenderer* renderer, int x, int y, const std::u16string& line);

	/// <summary>
	/// Draws the line.
	/// </summary>
	/// <param name="renderer">The renderer.</param>
	/// <param name="x">The x position of the text.</param>
	/// <param name="y">The y position of the text.</param>
	/// <param name="line">The line to render.</param>
	void drawLine(class IRenderer* renderer, int x, int y, const std::string& line);
	
	/// <summary>
	/// Sets the color of the text.
	/// </summary>
	/// <param name="color">The new color.</param>
	void setColor(const Color& color);
	
	/// <summary>
	/// Sets the shadow color of the text.
	/// </summary>
	/// <param name="color">The new shadow color.</param>
	void setShadowColor(const Color& color);
	
	/// <summary>
	/// When the text is rendered, the oppacity of the
	/// text will be modulated by this alpha value.
	/// </summary>
	/// <param name="alpha">The alpha multiplied into render operations.</param>
	void setAlphaMod(uint8_t alpha);

private:
	TTF_Font* font;
	SDL_Color fontColor;
	int shadowDistance;
	SDL_Color shadowColor;
	float alphaModulation;

	void drawLine(class IRenderer* renderer, int x, int y, const std::u16string& line, SDL_Color color);
};