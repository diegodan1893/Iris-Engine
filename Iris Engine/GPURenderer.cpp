#include "GPURenderer.h"
#include "GPUTexture.h"
#include <SDL_gpu.h>
#include <cmath>

GPURenderer::GPURenderer(SDL_Window* window)
	:scalingFactor(1.0f)
{
	int w, h;
	Uint32 windowID;

	SDL_GetWindowSize(window, &w, &h);
	windowID = SDL_GetWindowID(window);

	GPU_SetInitWindow(windowID);
	windowTarget = GPU_Init(w, h, GPU_INIT_ENABLE_VSYNC);

	if (windowTarget)
	{
		valid = true;

		// Create intermediate buffer
		virtualScreen = (GPUTexture*)createTexture(TextureFormat::RGB, TextureAccess::TARGET, w, h);
		currentTarget = screen = virtualScreen->getTarget();
		screenPosition = Vector2<float>(w / 2.0f, h / 2.0f);

		// Load shaders
		testShader.loadProgram();
		dissolveShader.loadProgram();
		imageDissolveShader.loadProgram();
		colorGradingShader.loadProgram();
	}
	else
	{
		valid = false;
	}
}

GPURenderer::~GPURenderer()
{
	GPU_Quit();
}

bool GPURenderer::isValid() const
{
	return valid;
}

bool GPURenderer::getFullscreen()
{
	return GPU_GetFullscreen();
}

void GPURenderer::setFullScreen(bool fullscreen)
{
	int virtualW = screen->base_w;
	int virtualH = screen->base_h;

	if (fullscreen)
	{
		// Enable fullscreen
		GPU_SetFullscreen(true, true);

		// Get new resolution
		int w = windowTarget->base_w;
		int h = windowTarget->base_h;

		if (virtualW > virtualH)
		{
			// Scale so that the width of the game is the same as the width of the screen
			scalingFactor = (float)w / virtualW;
		}
		else
		{
			// Scale so that the height of the game is the same as the height of the screen
			scalingFactor = (float)h / virtualH;
		}

		screenPosition.x = w / 2.0f;
		screenPosition.y = h / 2.0f;
	}
	else
	{
		GPU_SetFullscreen(false, true);
		
		scalingFactor = 1.0f;
		screenPosition.x = windowTarget->base_w / 2.0f;
		screenPosition.y = windowTarget->base_h / 2.0f;
	}
}

Vector2<int> GPURenderer::getWindowResolution()
{
	return Vector2<int>(windowTarget->base_w, windowTarget->base_h);
}

void GPURenderer::clear()
{
	GPU_Clear(currentTarget);
}

void GPURenderer::present()
{
	// Render to target
	GPU_Flip(currentTarget);

	// If we want to render to the screen, copy the intermediate buffer to the actual screen
	if (currentTarget == screen)
	{
		GPU_Clear(windowTarget);
		GPU_BlitScale(
			virtualScreen->getInternalTexture(),
			nullptr,
			windowTarget,
			screenPosition.x,
			screenPosition.y,
			scalingFactor,
			scalingFactor
		);

		GPU_Flip(windowTarget);
	}
}

void GPURenderer::setRenderTarget(ITexture* texture)
{
	if (texture)
	{
		// Set the texture as the current target
		GPUTexture* gpuTexture = (GPUTexture*)texture;

		currentTarget = gpuTexture->getTarget();
	}
	else
	{
		// Texture is null: set the screen at the current target
		currentTarget = screen;
	}
}

void GPURenderer::copy(ITexture* texture, const Rect<float>* srcrect, const Rect<float>* dstrect)
{
	GPUTexture* gpuTexture = (GPUTexture*)texture;

	GPU_BlitRect(gpuTexture->getInternalTexture(), (GPU_Rect*)srcrect, currentTarget, (GPU_Rect*)dstrect);
}

ITexture* GPURenderer::createTexture(TextureFormat format, TextureAccess access, int w, int h)
{
	// @todo This seems to have a greater impact in performance that creating a texture with SDL
	GPU_FormatEnum textureFormat;

	switch (format)
	{
	case TextureFormat::RGB:
		textureFormat = GPU_FORMAT_RGB;
		break;

	case TextureFormat::RGBA8:
		textureFormat = GPU_FORMAT_RGBA;
		break;

	default:
		textureFormat = GPU_FORMAT_RGBA;
		break;
	}

	GPU_Image* internalTexture = GPU_CreateImage(w, h, textureFormat);

	if (internalTexture)
	{
		GPUTexture* texture = new GPUTexture(internalTexture);

		if (access == TextureAccess::TARGET)
		{
			// Create a render target for this texture
			texture->createRenderTarget();
		}

		return texture;
	}
	else
	{
		return nullptr;
	}
}

ITexture* GPURenderer::createTexture(SDL_Surface* surface)
{
	GPU_Image* internalTexture = GPU_CopyImageFromSurface(surface);

	if (internalTexture)
		return new GPUTexture(internalTexture);
	else
		return nullptr;
}

TestShader* GPURenderer::getTestShader()
{
	return &testShader;
}

DissolveShader* GPURenderer::getDissolveShader()
{
	return &dissolveShader;
}

ImageDissolveShader* GPURenderer::getImageDissolveShader()
{
	return &imageDissolveShader;
}

ColorGradingShader* GPURenderer::getColorGradingShader()
{
	return &colorGradingShader;
}
