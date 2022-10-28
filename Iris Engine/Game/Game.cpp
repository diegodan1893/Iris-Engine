#include "Game.h"
#include <cassert>

bool Game::instantiated = false;

Game::Game() : gameState(GameState::UNITINIALIZED)
{
	assert(!instantiated);
	instantiated = true;
}

Game::~Game()
{
}

void Game::start()
{
	if (gameState != GameState::UNITINIALIZED)
	{
		return;
	}
}
