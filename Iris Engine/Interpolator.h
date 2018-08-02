#pragma once

/// <summary>
/// Generates values between 0 and 1 based on the
/// duration of an animation and the elapsed
/// time of that animation.
/// </summary>
class Interpolator
{
public:
	Interpolator();
	virtual ~Interpolator() {}
	
	/// <summary>
	/// Starts an interpolation.
	/// </summary>
	/// <param name="duration">The duration of the animation.</param>
	/// <param name="reversed">if set to <c>true</c>, the interpolation will be reversed.</param>
	void start(float duration, bool reversed);
	
	/// <summary>
	/// Goes immediately to the end of the interpolation.
	/// </summary>
	void skip();
	
	/// <summary>
	/// Updates the elapsed time of the interpolation.
	/// </summary>
	/// <param name="elapsedSeconds">The elapsed time since the last call in seconds.</param>
	void update(float elapsedSeconds);
	
	/// <summary>
	/// Check if the interpolation has finished.
	/// </summary>
	/// <returns><c>true</c> if the interpolation has not finished; otherwise <c>false</c>.</returns>
	bool inTransition() const;
	
	/// <summary>
	/// Gets the current value of the interpolation.
	/// </summary>
	/// <returns>A number between 0 and 1.</returns>
	virtual float getStep() const = 0;

protected:	
	/// <summary>
	/// Gets the duration.
	/// </summary>
	/// <returns>The duration in seconds.</returns>
	float getDuration() const;
	
	/// <summary>
	/// Gets the current time.
	/// </summary>
	/// <returns>Elapsed seconds since the start of the interpolation.</returns>
	float getCurrentTime() const;

private:
	float duration;
	float currentTime;
	bool reversed;
};