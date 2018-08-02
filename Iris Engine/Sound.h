#pragma once

#include "Asset.h"
#include <SDL_mixer.h>

/// <summary>
/// Holds a sound asset that can be cached.
/// </summary>
/// <seealso cref="Asset" />
class Sound : public Asset
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Sound"/> class.
	/// </summary>
	/// <param name="path">The path.</param>
	Sound(const std::string& path);
	~Sound();
	
	/// <summary>
	/// Gets the size of the stream that was used
	/// to create the asset in bytes.
	/// </summary>
	/// <returns>
	/// The size of the asset in bytes.
	/// </returns>
	unsigned int getSize() const override;
	
	/// <summary>
	/// Loads the asset from the file specified
	/// in the path. Use <see cref="isValid" /> to
	/// check if the load was successfull.
	/// </summary>
	void load() override;
	
	/// <summary>
	/// Gets the Mix_Chunk with the loaded sound.
	/// </summary>
	/// <returns>A Mix_Chunk that can be played.</returns>
	Mix_Chunk* getChunk() const;

private:
	unsigned int size;
	SDL_RWops* stream;
	Mix_Chunk* chunk;
};