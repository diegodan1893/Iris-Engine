#include "GPUTexture.h"
#include <SDL_gpu.h>

GPUTexture::GPUTexture(GPU_Image* texture)
	:texture(texture),
	 target(nullptr)
{
	GPU_SetSnapMode(texture, GPU_SNAP_NONE);
}

GPUTexture::~GPUTexture()
{
	if (target)
		GPU_FreeTarget(target);

	GPU_FreeImage(texture);
}

void GPUTexture::setBlendMode(BlendMode blendMode)
{
	GPU_SetBlending(texture, true);

	switch (blendMode)
	{
	case BlendMode::NONE:
		GPU_SetBlending(texture, false);
		break;

	case BlendMode::BLEND:
		GPU_SetBlendMode(texture, GPU_BLEND_NORMAL);
		break;

	case BlendMode::PREMULTIPLIED:
		GPU_SetBlendMode(texture, GPU_BLEND_PREMULTIPLIED_ALPHA);
		break;

	case BlendMode::MULTIPLY:
		GPU_SetBlendMode(texture, GPU_BLEND_MULTIPLY);
		break;

	case BlendMode::ADD:
		GPU_SetBlendMode(texture, GPU_BLEND_ADD);
		break;

	case BlendMode::SUBSTRACT:
		GPU_SetBlendMode(texture, GPU_BLEND_SUBTRACT);
		break;

	case BlendMode::MOD_ALPHA:
		GPU_SetBlendMode(texture, GPU_BLEND_MOD_ALPHA);
		break;

	case BlendMode::SET_ALPHA:
		GPU_SetBlendMode(texture, GPU_BLEND_SET_ALPHA);
		break;

	case BlendMode::SET:
		GPU_SetBlendMode(texture, GPU_BLEND_SET);
		break;

	case BlendMode::KEEP_ALPHA:
		GPU_SetBlendMode(texture, GPU_BLEND_NORMAL_KEEP_ALPHA);
		break;

	case BlendMode::ADD_ALPHA:
		GPU_SetBlendMode(texture, GPU_BLEND_NORMAL_ADD_ALPHA);
		break;

	case BlendMode::FACTOR_ALPHA:
		GPU_SetBlendMode(texture, GPU_BLEND_NORMAL_FACTOR_ALPHA);
		break;

	default:
		break;
	}
}

void GPUTexture::setAlphaMod(uint8_t alpha)
{
	GPU_SetRGBA(texture, 255, 255, 255, alpha);
}

void GPUTexture::getSize(int* w, int* h)
{
	*w = texture->base_w;
	*h = texture->base_h;
}

void GPUTexture::updateTextureBytes(const unsigned char* bytes)
{
	GPU_UpdateImageBytes(texture, nullptr, bytes, texture->base_w * texture->bytes_per_pixel);
}

GPU_Image* GPUTexture::getInternalTexture()
{
	return texture;
}

GPU_Target* GPUTexture::getTarget()
{
	return target;
}

void GPUTexture::createRenderTarget()
{
	target = GPU_LoadTarget(texture);
}
