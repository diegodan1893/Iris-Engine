#include "CPUImage.h"
#include "Locator.h"
#include <SDL.h>
#include <SDL_image.h>

CPUImage::CPUImage(const std::string& path)
	:Asset(path),
	 img(nullptr)
{
	// Open stream from disk and check for errors
	stream = SDL_RWFromFile(path.c_str(), "r");

	if (stream)
	{
		valid = true;

		// Get the size of the stream
		size = SDL_RWsize(stream);
	}
	else
	{
		valid = false;

		Locator::getLogger()->log(
			LogCategory::FILE,
			LogPriority::ERROR,
			u8"Error opening file " + path + ":\n" + std::string(SDL_GetError())
		);
	}
}

CPUImage::~CPUImage()
{
	if (stream)
		SDL_RWclose(stream);

	if (img)
		SDL_FreeSurface(img);
}

unsigned int CPUImage::getSize() const
{
	return size;
}

void CPUImage::load()
{
	// Create image from stream
	img = IMG_Load_RW(stream, SDL_TRUE);

	if (!img)
	{
		Locator::getLogger()->log(
			LogCategory::FILE,
			LogPriority::ERROR,
			u8"Error creating CPU image:\n" + std::string(IMG_GetError())
		);
	}

	// Stream is closed, make it null
	stream = nullptr;
}

SDL_Surface* CPUImage::getImage() const
{
	return img;
}
