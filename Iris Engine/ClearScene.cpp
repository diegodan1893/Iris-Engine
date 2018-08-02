#include "ClearScene.h"
#include "GameObjectManager.h"
#include "BackgroundObject.h"
#include "Locator.h"

ClearScene::ClearScene(GameObjectManager* gameObjectManager, BackgroundObject* background, const std::string& file, bool enableMouseInput)
	:gameObjectManager(gameObjectManager),
	 background(background),
	 newBackground(file),
	 enableMouseInput(enableMouseInput)
{
}

bool ClearScene::ready()
{
	gameObjectManager->hideAll();
	background->setBackground(newBackground);

	Locator::getInput()->setMouseInputEnabled(enableMouseInput);

	return true;
}
