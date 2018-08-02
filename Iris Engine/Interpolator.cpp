#include "Interpolator.h"

Interpolator::Interpolator()
	:duration(0.0f),
	 currentTime(0.0f),
	 reversed(false)
{
}

void Interpolator::start(float duration, bool reversed)
{
	this->duration = duration;
	this->reversed = reversed;

	if (reversed)
		currentTime = duration;
	else
		currentTime = 0.0f;
}

void Interpolator::skip()
{
	currentTime = reversed ? 0.0f : duration;
}

void Interpolator::update(float elapsedSeconds)
{
	if (!reversed)
	{
		currentTime += elapsedSeconds;

		if (currentTime > duration)
			currentTime = duration;
	}
	else
	{
		currentTime -= elapsedSeconds;

		if (currentTime < 0.0f)
			currentTime = 0.0f;
	}
}

bool Interpolator::inTransition() const
{
	if (!reversed)
		return currentTime != duration;
	else
		return currentTime != 0.0f;
}

float Interpolator::getDuration() const
{
	return duration;
}

float Interpolator::getCurrentTime() const
{
	return currentTime;
}
