#include "ClickableMap.h"
#include "Locator.h"
#include "Config.h"
#include <SDL_image.h>

ClickableMap::ClickableMap(const std::string& file)
	:Object(Config::values().zindexes.backgrounds),
	 autoDisableOnClick(true)
{
	map = IMG_Load((Config::values().paths.gui + file).c_str());

	if (map)
	{
		selectedPixel = previousSelectedPixel = 0;
	}
	else
	{
		Locator::getLogger()->log(
			LogCategory::OBJECT,
			LogPriority::ERROR,
			u8"Clickable map image could not be loaded:\n" + std::string(IMG_GetError())
		);
	}
}

ClickableMap::~ClickableMap()
{
	if (map)
		SDL_FreeSurface(map);
}

void ClickableMap::draw(IRenderer* renderer)
{
	// Do nothing
}

void ClickableMap::update(float elapsedSeconds)
{
	if (map)
	{
		// Map is enabled if the object is visible
		if (visible())
		{
			previousSelectedPixel = selectedPixel;
			selectedPixel = getSelectedPixel();

			auto selected = delegates.find(selectedPixel);
			auto previous = delegates.find(previousSelectedPixel);

			// onClick
			if (Locator::getInput()->mouseButtonJustPressed(SDL_BUTTON_LEFT))
			{
				if (selected != delegates.end() && selected->second.onClick)
				{
					selected->second.onClick();

					if (autoDisableOnClick)
						setVisible(false);
				}
			}

			if (selectedPixel != previousSelectedPixel)
			{
				// onEnter
				if (selected != delegates.end() && selected->second.onMouseEnter)
					selected->second.onMouseEnter();

				// onExit
				if (previous != delegates.end() && previous->second.onMouseExit)
					previous->second.onMouseExit();
			}
		}
		else
		{
			if (selectedPixel != 0)
				selectedPixel = previousSelectedPixel = 0;
		}
	}
}

void ClickableMap::setDisableOnClick(bool disableOnClick)
{
	autoDisableOnClick = disableOnClick;
}

void ClickableMap::setOnMouseEnter(Uint8 r, Uint8 g, Uint8 b, std::function<void(void)> function)
{
	Uint32 mappedColor = SDL_MapRGB(map->format, r, g, b);

	delegates[mappedColor].onMouseEnter = function;
}

void ClickableMap::setOnMouseExit(Uint8 r, Uint8 g, Uint8 b, std::function<void(void)> function)
{
	Uint32 mappedColor = SDL_MapRGB(map->format, r, g, b);

	delegates[mappedColor].onMouseExit = function;
}

void ClickableMap::setOnClick(Uint8 r, Uint8 g, Uint8 b, std::function<void(void)> function)
{
	Uint32 mappedColor = SDL_MapRGB(map->format, r, g, b);

	delegates[mappedColor].onClick = function;
}

Uint32 ClickableMap::getSelectedPixel()
{
	// Get mouse coordinates
	int x, y;
	Locator::getInput()->getMouseCoordinates(x, y);

	if (x >= 0 && x < map->w && y >= 0 && y < map->h)
	{
		int bpp = map->format->BytesPerPixel;
		Uint8* p = (Uint8*)map->pixels + y * map->pitch + x * bpp;

		switch (bpp) {
		case 1:
			return *p;
			break;

		case 2:
			return *(Uint16*)p;
			break;

		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] << 16;
			break;

		case 4:
			return *(Uint32 *)p;
			break;

		default:
			return 0;
		}
	}
	else
	{
		return SDL_MapRGB(map->format, 0, 0, 0);
	}
}
