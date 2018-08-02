#include "Cursor.h"
#include "Locator.h"
#include "Config.h"
#include <SDL.h>
#include <SDL_image.h>

Cursor::Cursor(const std::string& file, int hotX, int hotY)
{
	SDL_Surface* surface = IMG_Load((Config::values().paths.gui + file).c_str());

	if (surface)
	{
		cursor = SDL_CreateColorCursor(surface, hotX, hotY);
		SDL_FreeSurface(surface);

		if (!cursor)
		{
			Locator::getLogger()->log(
				LogCategory::SYSTEM,
				LogPriority::ERROR,
				u8"Cursor could not be created:\n" + std::string(SDL_GetError())
			);
		}
	}
	else
	{
		cursor = nullptr;

		Locator::getLogger()->log(
			LogCategory::SYSTEM,
			LogPriority::ERROR,
			u8"Cursor image could not be loaded:\n" + std::string(SDL_GetError())
		);
	}
}

Cursor::~Cursor()
{
	if (cursor)
		SDL_FreeCursor(cursor);
}

SDL_Cursor* Cursor::getCursor() const
{
	return cursor;
}
