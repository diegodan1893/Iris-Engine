#include "EaseOutInterpolator.h"

float EaseOutInterpolator::getStep() const
{
	float time = getCurrentTime() / getDuration();
	return -1 * time * (time - 2.0f);
}
