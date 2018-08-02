#include "GameObjectManager.h"
#include "Locator.h"
#include "IRenderer.h"
#include <algorithm>

GameObjectManager::GameObjectManager()
	:timer(0),
	 minimumElapsedTime(0)
{
	now = SDL_GetPerformanceCounter();
	last = SDL_GetPerformanceCounter();
}

GameObjectManager::~GameObjectManager()
{
	// Deallocate objects
	std::for_each(objects.begin(), objects.end(), ObjectDeallocator());
}

void GameObjectManager::add(Object* object)
{
	objects.insert(std::pair<int, Object*>(object->getZindex(), object));
}

bool GameObjectManager::remove(Object* object)
{
	bool found = false;
	std::multimap<int, Object*>::iterator element;

	// Find the object to remove
	auto range = objects.equal_range(object->getZindex());

	for (auto it = range.first; !found && it != range.second; ++it)
	{
		if (it->second == object)
		{
			found = true;
			element = it;
		}
	}

	if (found)
	{
		objects.erase(element);
	}

	return found;
}

void GameObjectManager::updateAll()
{
	last = now;
	now = SDL_GetPerformanceCounter();

	float elapsedSeconds = ((now - last) / (float)SDL_GetPerformanceFrequency());

	// @todo This is a hack and doesn't allow to disable VSync
	// For some reason, in fullscreen there are some cases where
	// elapsedSeconds is not correct, as it seems that while the game
	// waits for VSync, the time is measured as if there was no wait
	// after FPS drops.
	if (elapsedSeconds < minimumElapsedTime / 2)
	{
		float remainingTime = minimumElapsedTime - elapsedSeconds;
		SDL_Delay(remainingTime * 900);

		now = SDL_GetPerformanceCounter();
		elapsedSeconds = ((now - last) / (float)SDL_GetPerformanceFrequency());
	}
	// End of hack

	for (auto it = objects.begin(); it != objects.end(); ++it)
		it->second->update(elapsedSeconds);

	updateTimer(elapsedSeconds);
}

void GameObjectManager::drawAll(IRenderer* renderer) const
{
	for (auto it = objects.begin(); it != objects.end(); ++it)
		it->second->draw(renderer);
}

void GameObjectManager::hideAll()
{
	for (auto it = objects.begin(); it != objects.end(); ++it)
		it->second->setVisible(false);
}

void GameObjectManager::clear()
{
	// Deallocate objects
	std::for_each(objects.begin(), objects.end(), ObjectDeallocator());

	objects.clear();
}

void GameObjectManager::startTimer(float seconds)
{
	if (seconds > 0)
		timer = seconds;
	else
		timer = 0;
}

bool GameObjectManager::timerFinished()
{
	return timer == 0;
}

void GameObjectManager::calculateMinimumElapsedTime()
{
	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);

	minimumElapsedTime = 1.0f / displayMode.refresh_rate;
}

void GameObjectManager::updateTimer(float elapsedSeconds)
{
	if (Locator::getInput()->userWantsToSkip())
	{
		// Skip timer
		timer = 0;
	}
	else
	{
		if (timer > 0)
		{
			timer -= elapsedSeconds;

			if (timer < 0)
				timer = 0;
		}
	}
}
