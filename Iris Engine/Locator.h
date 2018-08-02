#pragma once

#include "ICache.h"
#include "ILogger.h"
#include "IInput.h"
#include "IAudio.h"

/// <summary>
/// Registers and locates the services
/// exposed to the rest of the engine.
/// </summary>
class Locator
{
public:
	static void provide(ILogger* service);
	static void provide(ICache* service);
	static void provide(IInput* service);
	static void provide(IAudio* service);

	static ILogger* getLogger();
	static ICache* getCache();
	static IInput* getInput();
	static IAudio* getAudio();

private:
	static ILogger* logger;
	static ICache* cache;
	static IInput* input;
	static IAudio* audio;
};