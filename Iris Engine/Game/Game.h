#pragma once

/// @brief Main class of the engine.
/// Initializes and runs the game loop.
class Game
{
public:
	Game();
	~Game();

	void start();

private:
	enum class GameState
	{
		UNITINIALIZED,
		PLAYING,
		EXITING
	};

	static bool instantiated;

	GameState gameState;
};
