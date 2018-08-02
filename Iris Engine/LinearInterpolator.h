#pragma once

#include "Interpolator.h"

/// <summary>
/// Interpolates using a linear interpolation.
/// There is no acceleration.
/// </summary>
/// <seealso cref="Interpolator" />
class LinearInterpolator : public Interpolator
{
public:	
	/// <summary>
	/// Gets the current value of the interpolation.
	/// </summary>
	/// <returns>
	/// A number between 0 and 1.
	/// </returns>
	float getStep() const override;
};