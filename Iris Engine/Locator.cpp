#include "Locator.h"

ILogger* Locator::logger;
ICache* Locator::cache;
IInput* Locator::input;
IAudio* Locator::audio;

void Locator::provide(ILogger* service)
{
	logger = service;
}

void Locator::provide(ICache* service)
{
	cache = service;
}

void Locator::provide(IInput * service)
{
	input = service;
}

void Locator::provide(IAudio* service)
{
	audio = service;
}

ILogger* Locator::getLogger()
{
	return logger;
}

ICache* Locator::getCache()
{
	return cache;
}

IInput * Locator::getInput()
{
	return input;
}

IAudio * Locator::getAudio()
{
	return audio;
}
