#pragma once

#include "Object.h"
#include <string>
#include <unordered_map>
#include <functional>

/// <summary>
/// An object that makes certain areas of the screen clickable.
/// It uses an image as a map. Each color will be a different
/// clickable region.
/// </summary>
/// <seealso cref="Object" />
class ClickableMap : public Object
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="ClickableMap"/> class.
	/// </summary>
	/// <param name="file">The path to the image to use as the map.</param>
	ClickableMap(const std::string& file);
	~ClickableMap();
	
	/// <summary>
	/// Draws this object to the specified renderer context.
	/// </summary>
	/// <param name="renderer">The renderer.</param>
	void draw(class IRenderer* renderer) override;
	
	/// <summary>
	/// Updates this instance.
	/// </summary>
	/// <param name="elapsedSeconds">The elapsed seconds.</param>
	void update(float elapsedSeconds) override;
	
	/// <summary>
	/// Sets whether or not the clickable map should be disabled
	/// after the user has clicked on it.
	/// </summary>
	/// <param name="disableOnClick">
	/// if set to <c>true</c>, the map will be disabled automatically once the user has clicked on it.
	/// </param>
	void setDisableOnClick(bool disableOnClick);

	// Delegates	
	/// <summary>
	/// Sets a delegate function to be called when the mouse enters
	/// a region with the specified color.
	/// </summary>
	/// <param name="r">The red component of the color of the region.</param>
	/// <param name="g">The green component of the color of the region.</param>
	/// <param name="b">The blue component of the color of the region.</param>
	/// <param name="function">The function to call.</param>
	void setOnMouseEnter(Uint8 r, Uint8 g, Uint8 b, std::function<void(void)> function);
	
	/// <summary>
	/// Sets a delegate function to be called when the mouse leaves
	/// a region with the specified color.
	/// </summary>
	/// <param name="r">The red component of the color of the region.</param>
	/// <param name="g">The green component of the color of the region.</param>
	/// <param name="b">The blue component of the color of the region.</param>
	/// <param name="function">The function to call.</param>
	void setOnMouseExit(Uint8 r, Uint8 g, Uint8 b, std::function<void(void)> function);
	
	/// <summary>
	/// Sets a delegate function to be called when the player clicks
	/// a region with the specified color.
	/// </summary>
	/// <param name="r">The red component of the color of the region.</param>
	/// <param name="g">The green component of the color of the region.</param>
	/// <param name="b">The blue component of the color of the region.</param>
	/// <param name="function">The function to call.</param>
	void setOnClick(Uint8 r, Uint8 g, Uint8 b, std::function<void(void)> function);

private:
	// Image to use as map
	std::string mapPath;

	// Selected pixel
	Uint32 selectedPixel, previousSelectedPixel;

	// If true, the map will be disabled after the first onClick
	bool autoDisableOnClick;

	// Delegates
	struct Delegates
	{
		std::function<void(void)> onClick;
		std::function<void(void)> onMouseEnter;
		std::function<void(void)> onMouseExit;
	};
	std::unordered_map<Uint32, Delegates> delegates;

	Uint32 getSelectedPixel(class CPUImage* mapImage);
	Uint32 mapColor(Uint8 r, Uint8 g, Uint8 b);
};
