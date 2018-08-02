#include "Sprite.h"
#include "Locator.h"
#include "IRenderer.h"
#include "ITexture.h"
#include <SDL_image.h>

Sprite::Sprite(const std::string& path, IRenderer* renderer)
	:Asset(path),
	 texture(nullptr),
	 renderer(renderer)
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

Sprite::~Sprite()
{
	if (stream)
		SDL_RWclose(stream);

	if (texture)
		delete texture;
}

unsigned int Sprite::getSize() const
{
	return size;
}

void Sprite::load()
{
	// Create texture from stream
	SDL_Surface* surface = IMG_Load_RW(stream, SDL_TRUE);
	texture = renderer->createTexture(surface);

	if (!texture)
	{
		Locator::getLogger()->log(
			LogCategory::CACHE,
			LogPriority::ERROR,
			u8"Texture for file " + getPath() + u8"could not be created: " + std::string(SDL_GetError())
		);
	}

	// Set blend mode
	texture->setBlendMode(BlendMode::BLEND);

	// Save texture size
	textureSize.x = surface->clip_rect.w;
	textureSize.y = surface->clip_rect.h;

	SDL_FreeSurface(surface);

	// Stream is closed, make it null
	stream = nullptr;
}

ITexture* Sprite::getTexture() const
{
	return texture;
}

Vector2<int> Sprite::getTextureSize() const
{
	return textureSize;
}
