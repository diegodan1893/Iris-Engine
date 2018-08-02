#pragma once

#include "Interpolator.h"

/// <summary>
/// Interpolates using a quadratic ease in.
/// Accelerates from zero velocity.
/// </summary>
/// <seealso cref="Interpolator" />
class EaseInInterpolator : public Interpolator
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