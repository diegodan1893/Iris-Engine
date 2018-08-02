#include "TransitionComponent.h"
#include <cmath>

TransitionComponent::TransitionComponent()
	:step(1.0f),
	 target(1.0f)
{
}

void TransitionComponent::start(float time, bool reversed)
{
	if (!reversed)
	{
		step = 0.0f;
		target = 1.0f;

		speed = 1.0f / time;
	}
	else
	{
		step = 1.0f;
		target = 0.0f;

		speed = -1.0f / time;
	}
}

void TransitionComponent::skip()
{
	step = target;
}

void TransitionComponent::update(float elapsedSeconds)
{
	step += speed * elapsedSeconds;

	if (speed > 0)
	{
		if (step > target)
			step = target;
	}
	else
	{
		if (step < target)
			step = target;
	}
}

bool TransitionComponent::inTransition() const
{
	return step != target;
}

float TransitionComponent::getStep() const
{
	return step;
}

uint8_t TransitionComponent::getStepAsAlpha() const
{
	return uint8_t(std::round(step * 255.0f));
}
