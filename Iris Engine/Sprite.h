#pragma once

#include "Asset.h"
#include "Vector.h"
#include <SDL.h>

/// <summary>
/// Holds a sprite asset that can be cached.
/// </summary>
/// <seealso cref="Asset" />
class Sprite : public Asset
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Sprite"/> class.
	/// </summary>
	/// <param name="path">The path.</param>
	/// <param name="renderer">The renderer used to create the texture.</param>
	Sprite(const std::string& path, class IRenderer* renderer);
	virtual ~Sprite();
	
	/// <summary>
	/// Gets the size of the stream that was used
	/// to create the asset in bytes.
	/// </summary>
	/// <returns>
	/// The size of the asset in bytes.
	/// </returns>
	virtual unsigned int getSize() const override;
	
	/// <summary>
	/// Loads the asset from the file specified
	/// in the path. Use <see cref="isValid" /> to
	/// check if the load was successfull.
	/// </summary>
	virtual void load() override;
	
	/// <summary>
	/// Gets the texture.
	/// </summary>
	/// <returns>The loaded <see cref="ITexture"/>.</returns>
	virtual class ITexture* getTexture() const;
	
	/// <summary>
	/// Gets the size of the texture.
	/// </summary>
	/// <returns>The size in pixels.</returns>
	virtual Vector2<int> getTextureSize() const;

private:
	unsigned int size;
	SDL_RWops* stream;
	class IRenderer* renderer;
	class ITexture* texture;

	Vector2<int> textureSize;
};
