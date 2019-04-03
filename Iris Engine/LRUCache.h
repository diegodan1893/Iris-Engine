#pragma once

#include "ICache.h"
#include "Asset.h"
#include <SDL.h>
#include <list>
#include <unordered_map>

/// <summary>
/// A cache that uses the LRU algorithm to
/// discard elements.
/// </summary>
/// <seealso cref="ICache" />
class LRUCache : public ICache
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="LRUCache"/> class.
	/// </summary>
	/// <param name="renderer">The renderer that will be used to create Sprites.</param>
	LRUCache(class IRenderer* renderer);
	~LRUCache();
	
	/// <summary>
	/// Gets a sprite.
	/// </summary>
	/// <param name="path">Path to the sprite.</param>
	/// <returns>
	/// The sprite located in path or <c>null</c> if it could not be loaded.
	/// </returns>
	Sprite* getSprite(const std::string& path) override;
	
	/// <summary>
	/// Gets a sound.
	/// </summary>
	/// <param name="path">The path.</param>
	/// <returns>
	/// The sound located in path or <c>null</c> if it could not be loaded.
	/// </returns>
	Sound* getSound(const std::string& path) override;
	
	/// <summary>
	/// Gets an image that can be used efficiently by the CPU.
	/// </summary>
	/// <param name="path">The path.</param>
	/// <returns>
	/// The image located in path or <c>null</c> if it could not be loaded.
	/// </returns>
	CPUImage* getCPUImage(const std::string& path) override;
	
	/// <summary>
	/// Determines whether the specified asset is present in the cache
	/// without loading it.
	/// </summary>
	/// <param name="path">The path.</param>
	/// <returns>
	///   <c>true</c> if the specified asset is present; otherwise, <c>false</c>.
	/// </returns>
	bool isPresent(const std::string& path) override;

private:
	enum AssetType;

	typedef std::list<Asset*>::iterator ObjectListIterator;

	// Cache properties
	unsigned int size;
	unsigned int maxSize;

	// Cache containers
	std::list<Asset*> cache;
	std::unordered_map<std::string, ObjectListIterator> assetMap;

	// Renderer, needed for creating sprites
	class IRenderer* renderer;
	
	/// <summary>
	/// Remove and destroy least recently used item.
	/// </summary>
	void removeLeastRecentlyUsed();
	
	/// <summary>
	/// Gets an asset.
	/// </summary>
	/// <param name="path">The path to the asset.</param>
	/// <param name="type">The type of asset.</param>
	/// <returns></returns>
	Asset* getAsset(const std::string& path, AssetType type);

	// Deallocator
	struct ObjectDeallocator
	{
		void operator()(Asset* asset) const
		{
			delete asset;
		}
	};

	// Asset types
	enum AssetType
	{
		SPRITE,
		SOUND,
		CPUIMAGE
	};
};
