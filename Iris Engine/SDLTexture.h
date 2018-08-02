#pragma once

#include "ITexture.h"
#include <SDL.h>

/// <summary>
/// A texture that uses the SDL library.
/// Deprecated.
/// </summary>
/// <seealso cref="ITexture" />
class SDLTexture : public ITexture
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="SDLTexture"/> class.
	/// </summary>
	/// <param name="texture">The texture.</param>
	SDLTexture(struct SDL_Texture* texture);
	~SDLTexture();
	
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
	/// Gets the internal representation of the texture.
	/// </summary>
	/// <returns>A pointer to the internal representation of the texture.</returns>
	struct SDL_Texture* getSDLTexture();

private:
	struct SDL_Texture* texture;
};