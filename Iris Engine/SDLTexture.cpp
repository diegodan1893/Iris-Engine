#include "SDLTexture.h"
#include "Locator.h"
#include <SDL.h>

SDLTexture::SDLTexture(SDL_Texture* texture)
	:texture(texture)
{
}

SDLTexture::~SDLTexture()
{
	SDL_DestroyTexture(texture);
}

void SDLTexture::setBlendMode(BlendMode blendMode)
{
	switch (blendMode)
	{
	case BlendMode::NONE:
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
		break;

	case BlendMode::BLEND:
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		break;

	case BlendMode::ADD:
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_ADD);
		break;

	case BlendMode::MOD_ALPHA:
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_MOD);
		break;

	default:
		Locator::getLogger()->log(
			LogCategory::RENDER,
			LogPriority::WARNING,
			u8"Using unsupported blending mode."
		);

		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		break;
	}
}

void SDLTexture::setAlphaMod(uint8_t alpha)
{
	SDL_SetTextureAlphaMod(texture, alpha);
}

void SDLTexture::getSize(int* w, int* h)
{
	SDL_QueryTexture(texture, nullptr, nullptr, w, h);
}

SDL_Texture* SDLTexture::getSDLTexture()
{
	return texture;
}
