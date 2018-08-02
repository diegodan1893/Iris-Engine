#include "EaseInInterpolator.h"

float EaseInInterpolator::getStep() const
{
	float time = getCurrentTime() / getDuration();
	return time * time;
}
