#pragma once

#include <string>

/// <summary>
/// A hardware mouse cursor.
/// </summary>
class Cursor
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Cursor"/> class.
	/// </summary>
	/// <param name="file">The file that contains the image used as a cursor.</param>
	/// <param name="hotX">The X-axis location of the upper left corner of the cursor relative to the actual mouse position.</param>
	/// <param name="hotY">The Y-axis location of the upper left corner of the cursor relative to the actual mouse position.</param>
	Cursor(const std::string& file, int hotX, int hotY);
	~Cursor();
	
	/// <summary>
	/// Gets the SDL_Cursor.
	/// </summary>
	/// <returns>The SDL_Cursor.</returns>
	struct SDL_Cursor* getCursor() const;

private:
	struct SDL_Cursor* cursor;
};