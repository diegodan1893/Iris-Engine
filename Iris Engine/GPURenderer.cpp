#include "GPURenderer.h"
#include "GPUTexture.h"
#include "Locator.h"
#include "Config.h"
#include <SDL_gpu.h>
#include <cmath>

GPURenderer::GPURenderer(SDL_Window* window)
	:scalingFactor(1.0f)
{
	int w = Config::values().screen.resolution.x;
	int h = Config::values().screen.resolution.y;
	int windowW, windowH;

	Uint32 windowID;

	windowID = SDL_GetWindowID(window);
	SDL_GetWindowSize(window, &windowW, &windowH);

	GPU_SetInitWindow(windowID);
	windowTarget = GPU_Init(windowW, windowH, GPU_INIT_ENABLE_VSYNC);

	if (windowTarget)
	{
		valid = true;

		// Create intermediate buffer
		virtualScreen = (GPUTexture*)createTexture(TextureFormat::RGB, TextureAccess::TARGET, w, h);
		currentTarget = screen = virtualScreen->getTarget();
		GPU_SetSnapMode(virtualScreen->getInternalTexture(), GPU_SNAP_POSITION_AND_DIMENSIONS);

		screenPosition = Vector2<float>(windowW / 2.0f, windowH / 2.0f);
		scalingFactor = (float)windowW / w;

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
	delete virtualScreen;

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

		// Letterboxing
		float ratioVirtual = (float)virtualW / virtualH;
		float ratioScreen = (float)w / h;

		scalingFactor = (ratioScreen < ratioVirtual) ? (float)w / virtualW : (float)h / virtualH;

		screenPosition.x = w / 2.0f;
		screenPosition.y = h / 2.0f;
	}
	else
	{
		GPU_SetFullscreen(false, true);
		
		scalingFactor = (float)windowTarget->base_w / screen->base_w;
		screenPosition.x = windowTarget->base_w / 2.0f;
		screenPosition.y = windowTarget->base_h / 2.0f;
	}
}

float GPURenderer::getScalingFactor()
{
	return scalingFactor;
}

Vector2<int> GPURenderer::getLetterboxingOffset()
{
	Vector2<int> offset;

	offset.x = std::abs(windowTarget->base_w - screen->base_w * scalingFactor) / 2.0f;
	offset.y = std::abs(windowTarget->base_h - screen->base_h * scalingFactor) / 2.0f;

	return offset;
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

void GPURenderer::saveScreenshot(const std::string& path, int w, int h)
{
	// Create a texture for the screenshot
	GPUTexture* screenshotTexture = (GPUTexture*)createTexture(TextureFormat::RGBA8, TextureAccess::TARGET, w, h);
	GPU_Target* screenshotTarget = screenshotTexture->getTarget();

	// Copy the screen to the texture scaling it to fit the desired resolution
	GPU_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = w;
	rect.h = h;

	GPU_BlitRect(virtualScreen->getInternalTexture(), nullptr, screenshotTarget, &rect);
	GPU_Flip(screenshotTarget);

	// Save the screenshot to a file
	GPU_bool success = GPU_SaveImage(screenshotTexture->getInternalTexture(), path.c_str(), GPU_FILE_AUTO);

	if (success)
	{
		Locator::getLogger()->log(
			LogCategory::RENDER,
			LogPriority::INFO,
			"Saved screenshot to the path: " + path
		);
	}
	else
	{
		Locator::getLogger()->log(
			LogCategory::RENDER,
			LogPriority::ERROR,
			"Couldn't save image to the path " + path
		);
	}
	
	// Delete temporal textures
	delete screenshotTexture;
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
