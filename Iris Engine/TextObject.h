#pragma once

#include "Object.h"
#include "FontProperties.h"
#include "FontComponent.h"
#include <string>
#include <vector>

/// <summary>
/// An object that can render a line of text
/// </summary>
/// <seealso cref="Object" />
class TextObject : public Object
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="TextObject"/> class.
	/// </summary>
	/// <param name="font">The font properties to use when rendering the text.</param>
	/// <param name="zindex">The zindex.</param>
	TextObject(FontProperties font, int zindex);

	virtual ~TextObject() {}
	
	/// <summary>
	/// Draws this object to the specified renderer context.
	/// </summary>
	/// <param name="renderer">The renderer.</param>
	virtual void draw(class IRenderer* renderer) override;
	
	/// <summary>
	/// Updates the specified renderer.
	/// </summary>
	/// <param name="renderer">The renderer.</param>
	virtual void update(float elapsedSeconds) override;
	
	/// <summary>
	/// Sets the text to display.
	/// </summary>
	/// <param name="text">The text.</param>
	void setText(const std::string& text);
	
 	/// <summary>
	/// Sets the maximum size.
	/// </summary>
	/// <param name="maxWidth">The maximum width.</param>
	/// <param name="maxHeight">The maximum height.</param>
	void setMaxSize(int maxWidth, int maxHeight);
	
	/// <summary>
	/// Sets what string to append to the end of the text
	/// when it is too long to fit within the text box.
	/// For example, "..." results in "Long text...".
	/// </summary>
	/// <param name="ellipsis">The ellipsis string.</param>
	void setEllipsis(const std::string& ellipsis);
	
	/// <summary>
	/// Sets the spacing of the lines.
	/// 0 is the recommended spacing for the font.
	/// </summary>
	/// <param name="spacing">The spacing.</param>
	void setSpacing(int spacing);

private:
	void updateText();

	FontComponent font;
	std::u16string text;
	std::u16string ellipsis;
	std::vector<std::u16string> lines;

	int maxWidth;
	int maxHeight;
	
	int lineSpacing;
};