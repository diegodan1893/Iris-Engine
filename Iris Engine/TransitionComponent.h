#pragma once

#include <inttypes.h>

class TransitionComponent
{
public:
	TransitionComponent();

	void start(float time, bool reversed);
	void skip();

	void update(float elapsedSeconds);

	bool inTransition() const;
	float getStep() const;
	uint8_t getStepAsAlpha() const;

private:
	float step;
	float target;
	float speed;
};