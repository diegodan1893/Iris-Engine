#include "WaitForTimer.h"
#include "GameObjectManager.h"

WaitForTimer::WaitForTimer(GameObjectManager* gameObjectManager)
	:gameObjectManager(gameObjectManager)
{
}

bool WaitForTimer::ready()
{
	return gameObjectManager->timerFinished();
}
