#pragma once

#include "Object.h"

/// <summary>
/// A filled rectangle
/// </summary>
/// <seealso cref="Object" />
class RectangleObject : public Object
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="RectangleObject"/> class.
	/// </summary>
	/// <param name="zindex">The zindex.</param>
	RectangleObject(int zindex);

	virtual ~RectangleObject();

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
	/// Sets the size of the rectangle.
	/// </summary>
	/// <param name="width">The width.</param>
	/// <param name="height">The height.</param>
	void setRectangleSize(int width, int height);
	
	/// <summary>
	/// Sets the color.
	/// </summary>
	/// <param name="color">The color.</param>
	void setColor(Color color);

private:
	Color color;
};