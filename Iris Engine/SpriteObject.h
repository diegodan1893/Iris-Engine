#pragma once

#include "Object.h"
#include <string>

/// <summary>
/// An object that represents a static or an animated
/// image that can be displayed on the screen.
/// </summary>
/// <seealso cref="Object" />
class SpriteObject : public Object
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="SpriteObject"/> class.
	/// </summary>
	/// <param name="file">
	/// The path to the image, relative to the sprites path defined in the config file.
	/// </param>
	/// <param name="zindex">The zindex.</param>
	/// <param name="position">The position.</param>
	/// <param name="origin">The coordinates of the origin of this object.</param>
	SpriteObject(
		const std::string& file,
		int zindex,
		Vector2<float> position = Vector2<float>(0, 0),
		Vector2<int> origin = Vector2<int>(0, 0)
	);
	
	/// <summary>
	/// Initializes a new instance of the <see cref="SpriteObject"/> class.
	/// </summary>
	/// <param name="file">
	/// The path to the image, relative to the folder specified in the <c>path</c> parameter.
	/// </param>
	/// <param name="path">The path to prepend to the <c>file"</c> parameter.</param>
	/// <param name="zindex">The zindex.</param>
	/// <param name="position">The position.</param>
	/// <param name="origin">The coordinates of the origin of this object.</param>
	SpriteObject(
		const std::string& file,
		const std::string& path,
		int zindex,
		Vector2<float> position = Vector2<float>(0, 0),
		Vector2<int> origin = Vector2<int>(0, 0)
	);

	virtual ~SpriteObject();
	
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

protected:
	bool getSizeWasSet() const;
	void setSizeWasSet(bool sizeWasSet);
	const std::string& getSpritePath() const;

private:
	bool sizeWasSet;
	std::string spritePath;

	void setSpritePath(const std::string& file);
};