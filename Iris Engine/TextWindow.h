#pragma once

#include "Object.h"
#include "FontComponent.h"
#include "Alignment.h"
#include <vector>
#include <string>

/// <summary>
/// The box where dialogue and narration is displayed.
/// </summary>
/// <seealso cref="Object" />
class TextWindow : public Object
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="TextWindow"/> class.
	/// </summary>
	/// <param name="renderer">The renderer.</param>
	TextWindow(class IRenderer* renderer);
	~TextWindow();
	
	/// <summary>
	/// Draws this object to the specified renderer context.
	/// </summary>
	/// <param name="renderer">The renderer.</param>
	virtual void draw(class IRenderer* renderer) override;
	
	/// <summary>
	/// Updates this instance.
	/// </summary>
	/// <param name="elapsedSeconds">The elapsed seconds since the last call to this method.</param>
	virtual void update(float elapsedSeconds) override;
	
	/// <summary>
	/// Displays the provided text with a typewriter
	/// animation.
	/// </summary>
	/// <param name="dialogueText">The dialogue text.</param>
	void setText(const std::string& dialogueText);
	
	/// <summary>
	/// Displays the provided text with a typewriter
	/// animation, showing the name of the character
	/// that says it.
	/// </summary>
	/// <param name="name">The name of the character that is speaking.</param>
	/// <param name="dialogueText">The dialogue text.</param>
	void setText(const std::string& name, const std::string& dialogueText);
	
	/// <summary>
	/// Appends the specified text to whatever was
	/// already being displayed with a typewriter
	/// animation.
	/// </summary>
	/// <param name="dialogueText">The dialogue text.</param>
	void append(const std::string& dialogueText);
	
	/// <summary>
	/// Sets the text alignment.
	/// </summary>
	/// <param name="align">The text alignment.</param>
	void setTextAlign(Alignment align);
	
	/// <summary>
	/// Resizes the text window to the specified
	/// size.
	/// </summary>
	/// <param name="newSize">The new size.</param>
	void resize(const Vector2<unsigned int>& newSize);
	
	/// <summary>
	/// Sets the margin of the text.
	/// </summary>
	/// <param name="newMargin">The new margin.</param>
	void setMargin(const Margin& newMargin);
	
	/// <summary>
	/// Clears the text being displayed in the window.
	/// </summary>
	void clearText();
	
	/// <summary>
	/// Called when the user has to make a choice.
	/// This will keep the text that was being
	/// displayed on the window but hide the
	/// indicator that prompts the player to advance
	/// to the next line of text.
	/// </summary>
	void enterQuestionMode();
	
	/// <summary>
	/// Checks whether or not the window is ready
	/// to accept new text.
	/// </summary>
	/// <returns>
	/// <c>true</c> if the window is ready to accept new text; otherwise, <c>false</c>.
	/// </returns>
	bool ready() const;
	
	/// <summary>
	/// Skips the typewriter animation or, if the
	/// text was too long, starts displaying the
	/// next page.
	/// </summary>
	void skip();

private:
	// Input
	class GameInput* gameInput;

	// Textures
	class IRenderer* renderer;
	class ITexture* background;
	class ITexture* indicator;
	class ITexture* transitionTexture;

	// Fonts
	FontComponent textFont;
	FontComponent nameFont;

	// Text
	std::vector<std::u16string> lines;
	Margin margin;
	Vector2<int> textPosition;
	unsigned int linesPerPage;
	int lineWidth;
	int lineSpacing;
	bool enableWordWrapping;
	bool formatJapaneseText;
	bool lastLineWasIndented;
	Alignment textAlign;

	// Name
	Vector2<int> namePosition;
	std::u16string name;

	// Indicator
	Rect<float> indicatorRect;
	bool showIndicatorAfterLastCharacter;

	// Typewriter effect
	bool animate;
	float time;
	float delay;
	std::size_t textPos;
	std::size_t textLength;
	int currentLine;

	bool isReady;
	bool waitingForText;
	bool showIndicator;
	bool transitionTextureHasBeenUpdated;

	void updateTextPositionsAndSizes();
	void updateIndicatorPosition();

	void drawText(int offsetX, int offsetY);
	void startAnimation(int page);
	void continueAnimation();
	bool animationFinished();
	class ITexture* createTexture(const std::string& file, uint8_t alpha = 255);
	void redrawTransitionTexture();

	void wordWrap(const std::u16string& text);
	void splitInLinesWithoutWordWrap(const std::u16string& text, bool startInNewLine);

	std::u16string convertToUTF16(const std::string& string);
};