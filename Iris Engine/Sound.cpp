#include "Sound.h"
#include "Locator.h"

Sound::Sound(const std::string& path)
	:Asset(path),
	 chunk(nullptr)
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
			"Error opening file " + path + ":\n" + std::string(SDL_GetError())
		);
	}
}

Sound::~Sound()
{
	if (stream)
		SDL_RWclose(stream);

	if (chunk)
	{
		Locator::getAudio()->stopSound(getPath());
		Mix_FreeChunk(chunk);
	}
}

unsigned int Sound::getSize() const
{
	return size;
}

void Sound::load()
{
	// Create chunk from stream
	chunk = Mix_LoadWAV_RW(stream, SDL_TRUE);

	// Stream is closed, make it null
	stream = nullptr;

	if (!chunk)
	{
		Locator::getLogger()->log(
			LogCategory::CACHE,
			LogPriority::ERROR,
			u8"Sound " + getPath() + u8"could not be created: " + std::string(Mix_GetError())
		);
	}
}

Mix_Chunk * Sound::getChunk() const
{
	return chunk;
}
