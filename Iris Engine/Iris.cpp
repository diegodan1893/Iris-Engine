#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

int main(int argc, char* argv[])
{
	{
		Game game;
		game.start();
	}

	// Quit SDL
	// This ensures all objects are deleted before quitting SDL
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	return 0;
}