#pragma once

#include "GPUTexture.h"

/// <summary>
/// A texture of format YCbCr420p that uses the
/// SDL_gpu library.
/// SDL_gpu doesn't support YCbCr yet. This texture
/// class emulates it with a set of textures and a
/// shader. It's faster than doing the conversion
/// to RGB on the CPU.
/// </summary>
/// <seealso cref="ITexture" />
class GPUYCbCrTexture : public GPUTexture
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="GPUYCbCrTexture"/> class.
	/// </summary>
	/// <param name="renderer">The renderer.</param>
	/// <param name="w">The width of the image.</param>
	/// <param name="h">The height of the image.</param>
	GPUYCbCrTexture(class GPURenderer* renderer, int w, int h);
	virtual ~GPUYCbCrTexture();
	
	/// <summary>
	/// Updates the texture from an array of pixel data.
	/// </summary>
	/// <param name="bytes">The pixel data.</param>
	virtual void updateTextureBytes(const unsigned char* bytes) override;

private:
	class GPURenderer* renderer;
	class ITexture* chroma;
};