#pragma once

#include "Vector.h"
#include "LinearInterpolator.h"
#include <SDL.h>

/// <summary>
/// An object that can tick and be drawn to the screen.
/// </summary>
class Object
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Object"/> class.
	/// </summary>
	/// <param name="zindex">The zindex. A higher zindex means the object will be drawn on top.</param>
	Object(int zindex);
	virtual ~Object();
	
	/// <summary>
	/// Draws this object to the specified renderer context.
	/// </summary>
	/// <param name="renderer">The renderer.</param>
	virtual void draw(class IRenderer* renderer) = 0;
		
	/// <summary>
	/// Updates this instance.
	/// </summary>
	/// <param name="elapsedSeconds">The elapsed seconds since the last call to this method.</param>
	virtual void update(float elapsedSeconds) = 0;
	
	/// <summary>
	/// Sets the coordinates of the origin of this object.
	/// If the position of the object is (0, 0), the pixel
	/// that will be at that position is the origin.
	/// </summary>
	/// <param name="x">The x position relative to the upper left corner of the object.</param>
	/// <param name="y">The y position relative to the upper left corner of the object.</param>
	void setOrigin(int x, int y);
	
	/// <summary>
	/// Sets the coordinates of the origin of this object.
	/// If the position of the object is (0, 0), the pixel
	/// that will be at that position is the origin.
	/// </summary>
	/// <param name="origin">The origin position relative to the upper left corner of the object.</param>
	void setOrigin(const Vector2<int>& origin);

	void setPosition(float x, float y);
	void setPosition(const Vector2<float>& position);

	const Vector2<float>& getPosition() const;
	
	/// <summary>
	/// Gets the zindex. A higher zindex means the
	/// object will be drawn on top.
	/// </summary>
	/// <returns>The zindex of the object.</returns>
	int getZindex() const;

	void setVisible(bool visible);
	bool visible() const;

	// Transitions	
	/// <summary>
	/// Starts a fade in transition with linear interpolation.
	/// </summary>
	/// <param name="time">The duration of the transition.</param>
	/// <param name="canBeSkipped">Whether or not this transition can be skipped by the player.</param>
	void startFadeIn(float time, bool canBeSkipped);
	
	/// <summary>
	/// Starts a fade out transition with linear interpolation.
	/// </summary>
	/// <param name="time">The duration of the transition.</param>
	/// <param name="canBeSkipped">Whether or not this transition can be skipped by the player.</param>>
	void startFadeOut(float time, bool canBeSkipped);
	
	/// <summary>
	/// Starts a move transition with the specified interpolator.
	/// </summary>
	/// <param name="x">The x position the object will move to.</param>
	/// <param name="y">The y position the object will move to.</param>
	/// <param name="time">The duration of the transition.</param>
	/// <param name="canBeSkipped">Whether or not this transition can be skipped by the player.</param>
	/// <param name="interpolator">The interpolator.</param>
	void move(float x, float y, float time, bool canBeSkipped, Interpolator* interpolator);

	/// <summary>
	/// Starts a move transition with the specified interpolator.
	/// </summary>
	/// <param name="target">The position the object will move to.</param>
	/// <param name="time">The duration of the transition.</param>
	/// <param name="canBeSkipped">Whether or not this transition can be skipped by the player.</param>
	/// <param name="interpolator">The interpolator.</param>
	void move(const Vector2<float> target, float time, bool canBeSkipped, Interpolator* interpolator);
	
	/// <summary>
	/// Skips all transitions including fades and movements.
	/// </summary>
	void skipTransition();
	
	/// <summary>
	/// Skips movement animations.
	/// </summary>
	void skipMovement();
	
	/// <summary>
	/// Returns whether or not the object is in any
	/// transition, including fades and movements.
	/// </summary>
	bool inTransition() const;

	// Animated sprites	
	/// <summary>
	/// Determines whether this object is an animated sprite.
	/// </summary>
	/// <returns>
	/// <c>true</c> if the object is an animated sprite; otherwise, <c>false</c>.
	/// </returns>
	bool isAnimatedSprite() const;
	
	/// <summary>
	/// Makes this object an animated sprite.
	/// </summary>
	/// <param name="frameCount">The number of frames of the sprite sheet.</param>
	/// <param name="cols">The number of columns.</param>
	/// <param name="rows">The number of rows.</param>
	/// <param name="fps">The framerate of the animation.</param>
	void defineSpriteSheet(int frameCount, int cols, int rows, int fps);
	
	/// <summary>
	/// Makes the animation to jump to an specified frame.
	/// Only works if the object is an animated sprite.
	/// </summary>
	/// <param name="frameNumber">The frame number.</param>
	void setFrame(int frameNumber);
	
	/// <summary>
	/// Gets the number of frames of the sprite sheet.
	/// </summary>
	/// <returns></returns>
	int getFrameCount() const;

protected:
	Rect<float>& getRect();
	void setSize(int w, int h);

	Vector2<int> getSize() const;

	void setValid(bool valid);
	bool valid() const;

	// Transitions
	bool inFade() const;
	bool inDissolve() const;
	bool inMovement() const;

	Uint8 getAlpha();
	void updateAlpha(float elapsedSeconds);
	float getAlphaRaw();
	void setAlphaRaw(float alpha);

	void startDissolve(float time, bool canBeSkipped);
	Uint8 getDissolveAlpha();
	void updateDissolveAlpha(float elapsedSeconds);

	void updateMovement(float elapsedSeconds);

	// Animated sprites
	void defineSpriteSheetRaw(int frameCount, int cols, int rows, int fps);
	Rect<float>& getFrameRect();
	void updateSpriteAnimation(float elapsedSeconds);

private:
	int zindex;
	Rect<float> rect;
	Vector2<int> origin;
	Vector2<float> position;
	bool isVisible;
	bool isValid;
	Uint8 alpha;

	// Transitions
	LinearInterpolator fade;
	LinearInterpolator dissolve;
	bool canBeSkipped;

	// Movement
	Vector2<float> startPosition;
	Vector2<float> targetPosition;
	Interpolator* movementInterpolator;

	// Animated sprites
	bool isSpriteSheet;
	Rect<float> frameRect;
	int frameCount;
	int cols;
	int rows;
	int fps;
	float currentFrame;

	void updateFrameRect(int frameNumber);
};