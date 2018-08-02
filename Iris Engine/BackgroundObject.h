#pragma once

#include "Object.h"
#include <string>

/// <summary>
/// An object used to draw the background of a scene.
/// </summary>
/// <seealso cref="Object" />
class BackgroundObject : public Object
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="BackgroundObject"/> class.
	/// </summary>
	/// <param name="zindex">The zindex.</param>
	BackgroundObject(int zindex);
	virtual ~BackgroundObject();
	
	/// <summary>
	/// Draws this object to the specified renderer context.
	/// </summary>
	/// <param name="renderer">The renderer.</param>
	virtual void draw(class IRenderer* renderer) override;
	
	/// <summary>
	/// Updates this instance.
	/// </summary>
	/// <param name="elapsedSeconds">The elapsed seconds.</param>
	virtual void update(float elapsedSeconds) override;
	
	/// <summary>
	/// Sets the image to use as the background.
	/// </summary>
	/// <param name="backgroundPath">
	///	The path to the image, relative to the backgrounds
	///	path specified in the config file.
	/// </param>
	void setBackground(const std::string& backgroundPath);
	
	/// <summary>
	/// Sets the image to use as the background with a dissolve
	/// transition using a linear interpolator.
	/// </summary>
	/// <param name="newBackground">The path to the new background.</param>
	/// <param name="time">The duration of the transition.</param>
	/// <param name="canBeSkipped">Whether or not this transition can be skipped by the player.</param>
	void startDissolveBackground(const std::string& newBackground, float time, bool canBeSkipped);
	
	/// <summary>
	/// Sets the image to use as the background with an
	/// image dissolve transition using a linear interpolator.
	/// </summary>
	/// <param name="time">The duration of the transition.</param>
	/// <param name="mask">The path to the image to use as a mask.</param>
	/// <param name="canBeSkipped">Whether or not this transition can be skipped by the player.</param>
	/// <param name="renderer">The renderer.</param>
	void startImageDissolve(float time, const std::string& mask, bool canBeSkipped, IRenderer* renderer);

private:
	std::string backgroundPath;
	std::string previousBackground;

	// Transitions
	bool inImageDissolve;
};