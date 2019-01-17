#pragma once

#include "Object.h"
#include "FontProperties.h"
#include "FontComponent.h"
#include <string>

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

private:
	FontComponent font;
	std::string text;
};