#include "GPUYCbCrTexture.h"
#include "GPURenderer.h"
#include <SDL_gpu.h>

GPUYCbCrTexture::GPUYCbCrTexture(GPURenderer* renderer, int w, int h)
	:GPUTexture(GPU_CreateImage(w, h, GPU_FORMAT_RGB)),
	 renderer(renderer)
{
	// Create a render target for the main texture
	createRenderTarget();

	// Create a texture for chroma components
	chroma = renderer->createTexture(TextureFormat::RGB, TextureAccess::STATIC, w / 2, h / 2);
}

GPUYCbCrTexture::~GPUYCbCrTexture()
{
	if (chroma)
		delete chroma;
}

void GPUYCbCrTexture::updateTextureBytes(const unsigned char* bytes)
{
	int w = getInternalTexture()->base_w;
	int h = getInternalTexture()->base_h;

	// Update luminance
	GPUTexture::updateTextureBytes(bytes);

	// Update chroma
	int chromaOffset = w * h * 3;
	chroma->updateTextureBytes(bytes + chromaOffset);

	// Convert to RGB
	Rect<float> rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = w;
	rect.h = h;

	YCbCrShader* shader = renderer->getYCbCrShader();
	shader->bind();
	shader->setParameters(chroma);

	renderer->setRenderTarget(this);
	renderer->copy(this, nullptr, &rect);
	renderer->present();
	renderer->setRenderTarget(nullptr);

	shader->unbind();
}
