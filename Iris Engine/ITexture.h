#pragma once

#include <cstdint>

/// <summary>
/// Supported blend modes for textures.
/// </summary>
enum class BlendMode
{
	NONE,
	BLEND,
	PREMULTIPLIED,
	MULTIPLY,
	ADD,
	SUBSTRACT,
	MOD_ALPHA,
	SET_ALPHA,
	SET,
	KEEP_ALPHA,
	ADD_ALPHA,
	FACTOR_ALPHA
};

/// <summary>
/// A structure that contains an efficient,
/// driver-specific representation of pixel data
/// </summary>
class ITexture
{
public:
	virtual ~ITexture() {}
	
	/// <summary>
	/// Sets the blend mode of the texture.
	/// </summary>
	/// <param name="blendMode">The blend mode.</param>
	virtual void setBlendMode(BlendMode blendMode) = 0;
	
	/// <summary>
	/// Sets the alpha modulation of the
	/// texture.
	/// </summary>
	/// <param name="alpha">The alpha value to be multiplied into copy operations.</param>
	virtual void setAlphaMod(uint8_t alpha) = 0;
	
	/// <summary>
	/// Gets the size of the texture.
	/// </summary>
	/// <param name="w">Filled with the width in pixels.</param>
	/// <param name="h">Filled with the width in pixels.</param>
	virtual void getSize(int* w, int* h) = 0;
	
	/// <summary>
	/// Updates the texture from an array of pixel data.
	/// </summary>
	/// <param name="bytes">The pixel data.</param>
	/// <param name="bytes_per_row">The bytes per row.</param>
	virtual void updateTextureBytes(const unsigned char* bytes) = 0;
};