#pragma once

#include <string>

/// <summary>
/// A cache that loads and holds assets.
/// </summary>
class ICache
{
public:
	virtual ~ICache() {}
	
	/// <summary>
	/// Gets a sprite.
	/// </summary>
	/// <param name="path">Path to the sprite.</param>
	/// <returns>The sprite located in path or <c>null</c> if it could not be loaded.</returns>
	virtual class Sprite* getSprite(const std::string& path) = 0;
	
	/// <summary>
	/// Gets a sound.
	/// </summary>
	/// <param name="path">The path.</param>
	/// <returns>The sound located in path or <c>null</c> if it could not be loaded.</returns>
	virtual class Sound* getSound(const std::string& path) = 0;
	
 	/// <summary>
	/// Determines whether the specified asset is present in the cache
	/// without loading it.
	/// </summary>
	/// <param name="path">The path.</param>
	/// <returns>
	///   <c>true</c> if the specified asset is present; otherwise, <c>false</c>.
	/// </returns>
	virtual bool isPresent(const std::string& path) = 0;
};