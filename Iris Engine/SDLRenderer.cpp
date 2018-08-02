#include "SDLRenderer.h"
#include "SDLTexture.h"
#include <SDL.h>

SDLRenderer::SDLRenderer(SDL_Window* window, int index, uint32_t flags)
{
	renderer = SDL_CreateRenderer(window, index, flags);

	if (renderer)
		valid = true;
	else
		valid = false;
}

SDLRenderer::~SDLRenderer()
{
	SDL_DestroyRenderer(renderer);
}

bool SDLRenderer::isValid() const
{
	return valid;
}

void SDLRenderer::clear()
{
	SDL_RenderClear(renderer);
}

void SDLRenderer::present()
{
	SDL_RenderPresent(renderer);
}

void SDLRenderer::setRenderTarget(ITexture* texture)
{
	if (texture)
	{
		SDLTexture* sdlTexture = (SDLTexture*)texture;
		SDL_SetRenderTarget(renderer, sdlTexture->getSDLTexture());
	}
	else
	{
		SDL_SetRenderTarget(renderer, nullptr);
	}
}

void SDLRenderer::copy(ITexture* texture, const Rect<float>* srcrect, const Rect<float>* dstrect)
{
	SDL_Rect src, dst;

	dst.x = dstrect->x;
	dst.y = dstrect->y;
	dst.w = dstrect->w;
	dst.h = dstrect->h;

	if (srcrect)
	{
		src.x = srcrect->x;
		src.y = srcrect->y;
		src.w = srcrect->w;
		src.h = srcrect->h;

		copySDLRect(texture, &src, &dst);
	}
	else
	{
		copySDLRect(texture, nullptr, &dst);
	}
}

ITexture* SDLRenderer::createTexture(TextureFormat format, TextureAccess access, int w, int h)
{
	Uint32 textureFormat;
	int textureAccess;

	switch (format)
	{
	case TextureFormat::RGBA8:
		textureFormat = SDL_PIXELFORMAT_RGBA8888;
		break;

	default:
		textureFormat = SDL_PIXELFORMAT_RGBA8888;
		break;
	}

	switch (access)
	{
	case TextureAccess::STATIC:
		textureAccess = SDL_TEXTUREACCESS_STATIC;
		break;

	case TextureAccess::STREAMING:
		textureAccess = SDL_TEXTUREACCESS_STREAMING;
		break;

	case TextureAccess::TARGET:
		textureAccess = SDL_TEXTUREACCESS_TARGET;
		break;

	default:
		textureAccess = SDL_TEXTUREACCESS_STATIC;
		break;
	}

	SDL_Texture* internalTexture = SDL_CreateTexture(renderer, textureFormat, textureAccess, w, h);

	if (internalTexture)
		return new SDLTexture(internalTexture);
	else
		return nullptr;
}

ITexture* SDLRenderer::createTexture(SDL_Surface* surface)
{
	SDL_Texture* internalTexture = SDL_CreateTextureFromSurface(renderer, surface);

	if (internalTexture)
		return new SDLTexture(internalTexture);
	else
		return nullptr;
}

void SDLRenderer::copySDLRect(ITexture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect)
{
	SDLTexture* sdlTexture = (SDLTexture*)texture;

	SDL_RenderCopy(renderer, sdlTexture->getSDLTexture(), srcrect, dstrect);
}
