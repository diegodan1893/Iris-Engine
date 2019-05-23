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

	// Create temporal buffers
	// We do it here to avoid allocating new memory every frame
	int lumaSize = w * h * 3;
	int chromaSize = w * h / 2 * 3;

	lumaBytes = new unsigned char[lumaSize];
	chromaBytes = new unsigned char[chromaSize];
}

GPUYCbCrTexture::~GPUYCbCrTexture()
{
	if (chroma)
		delete chroma;

	delete[] lumaBytes;
	delete[] chromaBytes;
}

void GPUYCbCrTexture::updateTextureBytes(const unsigned char* bytes)
{
	int w = getInternalTexture()->base_w;
	int h = getInternalTexture()->base_h;

	// Update luminance
	unsigned char* dst = lumaBytes;

	for (int i = 0; i < w * h; ++i, dst += 3)
		*dst = bytes[i];

	GPUTexture::updateTextureBytes(lumaBytes);

	// Update chroma
	unsigned int cb = w * h;
	unsigned int cr = cb + w / 2 * h / 2;
	dst = chromaBytes;

	for (int i = 0; i < w / 2 * h / 2; ++i, dst += 3)
	{
		dst[0] = bytes[cb++];
		dst[1] = bytes[cr++];
	}

	chroma->updateTextureBytes(chromaBytes);

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
