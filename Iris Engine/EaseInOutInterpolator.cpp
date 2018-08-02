#include "EaseInOutInterpolator.h"

float EaseInOutInterpolator::getStep() const
{
	float time = getCurrentTime() / (getDuration() / 2.0f);

	if (time < 1)
		return 1.0f / 2.0f * time * time;
	
	--time;

	return -1.0f / 2.0f * (time * (time - 2.0f) - 1.0f);
}
