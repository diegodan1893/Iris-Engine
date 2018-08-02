#include "LinearInterpolator.h"

float LinearInterpolator::getStep() const
{
	return getCurrentTime() / getDuration();
}
