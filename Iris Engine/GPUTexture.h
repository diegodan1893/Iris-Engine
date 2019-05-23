#pragma once

#include "ITexture.h"

/// <summary>
/// A texture that uses the
/// SDL_gpu library.
/// </summary>
/// <seealso cref="ITexture" />
class GPUTexture : public ITexture
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="GPUTexture"/> class.
	/// </summary>
	/// <param name="texture">The GPU_Image that contains the data of the texture.</param>
	GPUTexture(struct GPU_Image* texture);
	virtual ~GPUTexture();
	
	/// <summary>
	/// Sets the blend mode of the texture.
	/// </summary>
	/// <param name="blendMode">The blend mode.</param>
	void setBlendMode(BlendMode blendMode) override;
	
	/// <summary>
	/// Sets the alpha modulation of the
	/// texture.
	/// </summary>
	/// <param name="alpha">The alpha value to be multiplied into copy operations.</param>
	void setAlphaMod(uint8_t alpha) override;
	
	/// <summary>
	/// Gets the size of the texture.
	/// </summary>
	/// <param name="w">Filled with the width in pixels.</param>
	/// <param name="h">Filled with the width in pixels.</param>
	void getSize(int* w, int* h) override;
	
	/// <summary>
	/// Updates the texture from an array of pixel data.
	/// </summary>
	/// <param name="bytes">The pixel data.</param>
	/// <param name="bytesPerRow"></param>
	virtual void updateTextureBytes(const unsigned char* bytes) override;
	
	/// <summary>
	/// Gets the internal representation of
	/// the texture.
	/// </summary>
	/// <returns>A pointer to the internal representation of the texture.</returns>
	struct GPU_Image* getInternalTexture();
	
	/// <summary>
	/// Gets the renderer target of this
	/// texture.
	/// </summary>
	/// <returns>A pointer to the renderer target of this texture.</returns>
	struct GPU_Target* getTarget();
	
	/// <summary>
	/// Creates a render target for this
	/// texture.
	/// </summary>
	void createRenderTarget();

private:
	struct GPU_Image* texture;
	struct GPU_Target* target;
};
