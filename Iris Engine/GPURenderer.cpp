#include "GPURenderer.h"
#include "GPUTexture.h"
#include <SDL_gpu.h>
#include <cmath>

GPURenderer::GPURenderer(SDL_Window* window)
	:letterboxHorizontal(false),
	 letterboxVertical(false)
{
	int w, h;
	Uint32 windowID;

	SDL_GetWindowSize(window, &w, &h);
	windowID = SDL_GetWindowID(window);

	GPU_SetInitWindow(windowID);
	screen = currentTarget = GPU_Init(w, h, GPU_INIT_ENABLE_VSYNC);

	if (screen)
	{
		valid = true;

		// Load shaders
		testShader.loadProgram();
		dissolveShader.loadProgram();
		imageDissolveShader.loadProgram();
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

void GPURenderer::setFullScreen(bool fullscreen, int virtualW, int virtualH)
{
	if (fullscreen)
	{
		// Enable fullscreen
		GPU_SetFullscreen(true, true);

		// Get new resolution
		int w = screen->base_w;
		int h = screen->base_h;

		// Create a camera for letterboxing
		GPU_Camera camera = GPU_GetCamera(screen);

		if (virtualW > virtualH)
		{
			// Scale so that the width of the game is the same as the width of the screen
			camera.zoom = (float)w / virtualW;

			letterboxHorizontal = true;
			letterboxSize.x = virtualW;
			letterboxSize.y = std::ceil((h - virtualH * camera.zoom) / camera.zoom);
		}
		else
		{
			// Scale so that the height of the game is the same as the height of the screen
			camera.zoom = (float)h / virtualH;

			letterboxVertical = true;
			letterboxSize.x = std::ceil((w - virtualW * camera.zoom) / camera.zoom);
			letterboxSize.y = virtualH;
		}

		camera.x = -w / 2.0f + virtualW / 2.0f;
		camera.y = -h / 2.0f + virtualH / 2.0f;

		GPU_SetCamera(screen, &camera);

		if (letterboxSize.x == 0 || letterboxSize.y == 0)
			letterboxHorizontal = letterboxVertical = 0;

		screenSize.x = virtualW;
		screenSize.y = virtualH;
	}
	else
	{
		GPU_SetFullscreen(false, true);
		GPU_SetCamera(screen, NULL);

		letterboxHorizontal = letterboxVertical = false;
	}
}

Vector2<int> GPURenderer::getWindowResolution()
{
	return Vector2<int>(screen->base_w, screen->base_h);
}

void GPURenderer::clear()
{
	GPU_Clear(currentTarget);
}

void GPURenderer::present()
{
	if (currentTarget == screen)
	{
		// Apply letterboxing
		if (letterboxHorizontal)
		{
			GPU_RectangleFilled(currentTarget, 0, -letterboxSize.y, letterboxSize.x, 0, { 0, 0, 0, 255 });
			GPU_RectangleFilled(currentTarget, 0, screenSize.y, letterboxSize.x, letterboxSize.y + screenSize.y, { 0, 0, 0, 255 });
		}
		else if (letterboxVertical)
		{
			GPU_RectangleFilled(currentTarget, -letterboxSize.x, 0, 0, screenSize.y, { 0, 0, 0, 255 });
			GPU_RectangleFilled(currentTarget, screenSize.x, 0, letterboxSize.x + screenSize.x, screenSize.y, { 0, 0, 0, 255 });
		}
	}

	// Render to screen
	GPU_Flip(currentTarget);
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
