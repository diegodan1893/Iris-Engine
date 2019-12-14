#include "TextWindow.h"
#include "Config.h"
#include "Locator.h"
#include "IRenderer.h"
#include "ITexture.h"
#include "StringConverter.h"
#include <SDL_image.h>
#include <codecvt>

TextWindow::TextWindow(IRenderer* renderer)
	:Object(Config::values().zindexes.textWindow),
	 renderer(renderer),
	 gameInput(gameInput),
	 transitionTexture(nullptr),
	 textFont(Config::values().textWindow.fontProperties),
	 nameFont(Config::values().textWindow.nameFontProperties),
	 textAlign(Alignment::LEFT),
	 animate(false),
	 time(0),
	 isReady(false),
	 waitingForText(false),
	 showIndicator(true),
	 transitionTextureHasBeenUpdated(false)
{
	// Get position, size and margin from config file
	setPosition((float)Config::values().textWindow.position.x, (float)Config::values().textWindow.position.y);
	setSize(Config::values().textWindow.size.x, Config::values().textWindow.size.y);
	margin = Config::values().textWindow.margin;

	namePosition = Config::values().textWindow.namePos;

	lineSpacing = Config::values().textWindow.spacing;
	enableWordWrapping = Config::values().textWindow.wordWrapping;
	formatJapaneseText = Config::values().textWindow.formatJapaneseText;

	updateTextPositionsAndSizes();

	delay = Config::values().textWindow.characterDelay;

	// Create textures
	const std::string& guiPath = Config::values().paths.gui;
	background = createTexture(guiPath + Config::values().textWindow.background, Config::values().textWindow.backgroundAlpha);
	indicator = createTexture(guiPath + Config::values().textWindow.indicatorImage);
	transitionTexture = renderer->createTexture(TextureFormat::RGBA8, TextureAccess::TARGET, getRect().w, getRect().h);
	transitionTexture->setBlendMode(BlendMode::BLEND);

	if (indicator)
	{
		// Set indicatorRect
		indicatorRect.x = Config::values().textWindow.indicatorPosition.x + getPosition().x;
		indicatorRect.y = Config::values().textWindow.indicatorPosition.y + getPosition().y;

		int w, h;
		indicator->getSize(&w, &h);
		indicatorRect.w = w;
		indicatorRect.h = h;
		indicatorRect.w /= Config::values().textWindow.indicatorCols;
		indicatorRect.h /= Config::values().textWindow.indicatorRows;

		defineSpriteSheetRaw(
			Config::values().textWindow.indicatorFrameCount,
			Config::values().textWindow.indicatorCols,
			Config::values().textWindow.indicatorRows,
			Config::values().textWindow.indicatorFPS
		);

		Rect<float>& frameRect = getFrameRect();
		frameRect.w = indicatorRect.w;
		frameRect.h = indicatorRect.h;

		showIndicatorAfterLastCharacter = Config::values().textWindow.showIndicatorAfterLastCharacter;
	}
}

TextWindow::~TextWindow()
{
	delete background;
	delete indicator;

	if (transitionTexture)
		delete transitionTexture;
}

void TextWindow::draw(IRenderer* renderer)
{
	if (visible())
	{
		if (inFade())
		{
			renderer->copy(transitionTexture, nullptr, &getRect());
		}
		else
		{
			if (background)
				renderer->copy(background, nullptr, &getRect());

			if (!animate && indicator && showIndicator)
			{
				renderer->copy(indicator, &getFrameRect(), &indicatorRect);
			}

			//! @todo Draw Text
			// Rendering text each frame is inefficient, but I need to figure out
			// how to do premultipied alpha blending before this can be optimized.
			drawText((int)getPosition().x, (int)getPosition().y);
		}
	}
}

void TextWindow::update(float elapsedSeconds)
{
	// Update text window based on player input
	if (Locator::getInput()->userWantsToSkip() || Locator::getInput()->actionNext())
	{
		if (isReady)
			waitingForText = true;
		else
			skip();
	};

	// Update transitions
	if (inFade())
	{
		updateAlpha(elapsedSeconds);

		// In order to fade in or out without weird artifacts caused by
		// drawing several layers with the same alpha on top of each
		// other, we need to prerender the text window to a texture and
		// fade that texture.
		//
		//! @todo Now that I managed to get this working, I should use it
		// to avoid drawing the text every frame.
		if (!transitionTextureHasBeenUpdated)
			redrawTransitionTexture();

		transitionTexture->setAlphaMod(getAlpha());
	}
	else
	{
		if (transitionTextureHasBeenUpdated)
		{
			// Fade just finished
			transitionTextureHasBeenUpdated = false;
		}
	}

	// Animate text
	if (animate)
	{
		time += elapsedSeconds;
		textPos = (std::size_t)(time / delay);

		if (textPos >= textLength)
		{
			textPos = textLength;
			animate = false;

			isReady = animationFinished();
		}
	}

	// Animate indicator
	if (isAnimatedSprite())
		updateSpriteAnimation(elapsedSeconds);
}

void TextWindow::setText(const std::string& dialogueText)
{
	// Convert string to utf-16 so that it can be easily drawn character by character
	std::u16string text = StringConverter::convertToUTF16(dialogueText);

	// Clear current text
	clearText();

	// Word wrap
	if (enableWordWrapping)
		textFont.wordWrap(text, lineWidth, lines);
	else
		textFont.splitInLinesNoWordWrap(text, lineWidth, lines);

	// Prepare typewriter effect
	startAnimation(0);
	showIndicator = true;
	updateIndicatorPosition();
}

void TextWindow::setText(const std::string& name, const std::string& dialogueText)
{
	setText(dialogueText);
	this->name = StringConverter::convertToUTF16(name);
}

void TextWindow::append(const std::string& dialogueText)
{
	if (!dialogueText.empty())
	{
		// Convert string to utf-16 so that it can be easily drawn character by character
		std::u16string text = StringConverter::convertToUTF16(dialogueText);

		// New text is being drawn, update transition texture
		transitionTextureHasBeenUpdated = false;

		// Word wrap
		if (enableWordWrapping)
			textFont.wordWrap(text, lineWidth, lines);
		else
			textFont.splitInLinesNoWordWrap(text, lineWidth, lines);

		// Continue typewriter effect
		continueAnimation();
		showIndicator = true;
		updateIndicatorPosition();
	}
}

void TextWindow::setTextAlign(Alignment align)
{
	textAlign = align;
}

void TextWindow::resize(const Vector2<unsigned int>& newSize)
{
	setSize(newSize.x, newSize.y);
	updateTextPositionsAndSizes();
}

void TextWindow::setMargin(const Margin& newMargin)
{
	margin = newMargin;
	updateTextPositionsAndSizes();
}

void TextWindow::clearText()
{
	lines.clear();
	name.clear();
	showIndicator = false;
	transitionTextureHasBeenUpdated = false;
}

void TextWindow::enterQuestionMode()
{
	waitingForText = false;
	showIndicator = false;
}

bool TextWindow::ready() const
{
	return waitingForText;
}

void TextWindow::skip()
{
	if (animate)
	{
		animate = false;
		isReady = animationFinished();
	}
	else if (!isReady)
	{
		startAnimation(currentLine / linesPerPage + 1);
	}
}

void TextWindow::updateTextPositionsAndSizes()
{
	// Save the text position in a vector so that it can be read easily
	textPosition = Vector2<int>(margin.left, margin.top);

	// Calculate the width of the lines
	lineWidth = getSize().x - (margin.left + margin.right);

	// Calculate the number of lines that fit in one page
	int lineHeight = textFont.getLineSkip() + lineSpacing;
	linesPerPage = (getSize().y - (margin.top + margin.bottom)) / lineHeight;
}

void TextWindow::updateIndicatorPosition()
{
	if (showIndicatorAfterLastCharacter)
	{
		if (lines.empty())
		{
			indicatorRect.x = getPosition().x + textPosition.x;
			indicatorRect.y = getPosition().y + textPosition.y;
		}
		else
		{
			// Move the indicator next to the last character of the displayed text

			// X position: place the indicator to the right of the last line separated
			// by the distance of a space " "
			int lastLineWidth, spaceWidth;
			textFont.size(lines.back(), &lastLineWidth, nullptr);
			textFont.size(u" ", &spaceWidth, nullptr);

			indicatorRect.x = getPosition().x + textPosition.x + lastLineWidth + spaceWidth;

			// Y position: place the indicator at the center of the last line
			int lineHeight = textFont.getLineSkip() + lineSpacing;
			int lineY = getPosition().y + textPosition.y + lineHeight * ((lines.size() - 1) % linesPerPage);

			// lineHeight takes into account the recommended line space,
			// so we need to use fontHeight instead
			indicatorRect.y = lineY + (textFont.getFontHeight() / 2.0 - indicatorRect.h / 2.0);
		}
	}
}

void TextWindow::drawText(int offsetX, int offsetY)
{
	int x = textPosition.x + offsetX;
	int y = textPosition.y + offsetY;
	int lineHeight = textFont.getLineSkip() + lineSpacing;

	unsigned int numLines = currentLine + linesPerPage;
	if (numLines > lines.size())
		numLines = lines.size();

	int charsDrawn = 0;
	std::u16string substr;

	for (unsigned int i = currentLine; i < numLines; ++i)
	{
		const std::u16string* line = &lines[i];

		if (animate)
		{
			if (textPos - charsDrawn < line->length())
			{
				substr = line->substr(0, textPos - charsDrawn);
				line = &substr;
			}
		}

		if (!line->empty())
		{
			charsDrawn += line->length();

			// Align lines
			int w;
			int lineX = x;
			switch (textAlign)
			{
			case Alignment::CENTER:
				textFont.size(lines[i], &w, nullptr);
				lineX += lineWidth / 2.0f - w / 2.0f;
				break;

			case Alignment::RIGHT:
				textFont.size(lines[i], &w, nullptr);
				lineX += lineWidth - w;
				break;
			}

			textFont.drawLine(renderer, lineX, y + (i - currentLine) * lineHeight, *line);
		}
	}

	// Draw name
	if (!name.empty())
	{
		x = namePosition.x + offsetX;
		y = namePosition.y + offsetY;

		nameFont.drawLine(renderer, x, y, name);
	}
}

void TextWindow::startAnimation(int page)
{
	animate = true;
	currentLine = page * linesPerPage;
	textPos = 0;
	time = 0;
	isReady = false;
	waitingForText = false;

	textLength = 0;
	for (unsigned int i = currentLine; i < currentLine + linesPerPage && i < lines.size(); ++i)
	{
		if (!lines[i].empty())
			textLength += lines[i].length();
	}
}

void TextWindow::continueAnimation()
{
	animate = true;
	isReady = false;
	time = textLength * delay;
	textPos = textLength;
	waitingForText = false;

	// Recalculate text length
	textLength = 0;
	for (unsigned int i = currentLine; i < currentLine + linesPerPage && i < lines.size(); ++i)
	{
		if (!lines[i].empty())
			textLength += lines[i].length();
	}

	// If none of the new characters fit in the page, go to the next one
	if (textPos >= textLength)
		startAnimation(currentLine / linesPerPage + 1);
}

bool TextWindow::animationFinished()
{
	return currentLine + linesPerPage >= lines.size();
}

ITexture* TextWindow::createTexture(const std::string& file, uint8_t alpha)
{
	ITexture* texture;
	SDL_Surface* surface = IMG_Load(file.c_str());

	if (surface)
	{
		texture = renderer->createTexture(surface);
		SDL_FreeSurface(surface);

		if (texture)
		{
			texture->setAlphaMod(alpha);
		}
		else
		{
			Locator::getLogger()->log(
				LogCategory::VIDEO,
				LogPriority::ERROR,
				u8"Texture could not be created:\n" + std::string(SDL_GetError())
			);
		}
	}
	else
	{
		texture = nullptr;

		Locator::getLogger()->log(
			LogCategory::OBJECT,
			LogPriority::ERROR,
			u8"Texture could not be loaded:\n" + std::string(IMG_GetError())
		);
	}

	return texture;
}

void TextWindow::redrawTransitionTexture()
{
	Rect<float> rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = getRect().w;
	rect.h = getRect().h;

	// Start rendering to texture
	renderer->setRenderTarget(transitionTexture);
	renderer->clear();

	// Copy background without alpha blending to avoid applying alpha twice
	background->setBlendMode(BlendMode::SET);
	renderer->copy(background, nullptr, &rect);
	background->setBlendMode(BlendMode::BLEND);

	// Draw text
	drawText(0, 0);

	// Stop rendering to texture
	renderer->setRenderTarget(nullptr);
}
