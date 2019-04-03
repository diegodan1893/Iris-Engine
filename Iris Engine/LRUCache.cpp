#include "LRUCache.h"
#include "Config.h"
#include "Locator.h"
#include "Sprite.h"
#include "Sound.h"
#include "CPUImage.h"
#include "IRenderer.h"
#include <algorithm>

LRUCache::LRUCache(IRenderer* renderer)
	:size(0),
	 renderer(renderer)
{
	maxSize = Config::values().cache.maxSizeInMiB * (1 << 20);
}

LRUCache::~LRUCache()
{
	std::for_each(cache.begin(), cache.end(), ObjectDeallocator());
}

Sprite* LRUCache::getSprite(const std::string& path)
{
	return (Sprite*)getAsset(path, LRUCache::SPRITE);
}

Sound* LRUCache::getSound(const std::string& path)
{
	return (Sound*)getAsset(path, LRUCache::SOUND);
}

CPUImage* LRUCache::getCPUImage(const std::string & path)
{
	return (CPUImage*)getAsset(path, LRUCache::CPUIMAGE);
}

bool LRUCache::isPresent(const std::string & path)
{
	auto it = assetMap.find(path);

	return it != assetMap.end();
}

void LRUCache::removeLeastRecentlyUsed()
{
	auto last = cache.end();
	--last;

	Asset* element = *last;

	// Remove element from containers
	Locator::getLogger()->log(LogCategory::CACHE, LogPriority::INFO, "Unloading " + element->getPath() + " from cache");
	assetMap.erase(element->getPath());
	cache.erase(last);

	// Update size
	size -= element->getSize();

	// Destroy element
	delete element;
}

Asset* LRUCache::getAsset(const std::string& path, AssetType type)
{
	Asset* result = nullptr;

	// Check if the asset is already cached
	auto it = assetMap.find(path);

	if (it == assetMap.end())
	{
		// The asset is not in the cache, load it
		Locator::getLogger()->log(LogCategory::CACHE, LogPriority::INFO, u8"Loading " + path + u8" from disk.");

		Asset* asset;

		switch (type)
		{
		case LRUCache::SPRITE:
			asset = new Sprite(path, renderer);
			break;

		case LRUCache::SOUND:
			asset = new Sound(path);
			break;

		case LRUCache::CPUIMAGE:
			asset = new CPUImage(path);
			break;

		default:
			Locator::getLogger()->log(LogCategory::CACHE, LogPriority::ERROR, u8"Trying to cache an invalid asset type");
			return nullptr;
		}

		if (asset->isValid())
		{
			// File exists and can be loaded. Check size.
			unsigned int assetSize = asset->getSize();

			if (assetSize > maxSize)
			{
				// File is too big
				Locator::getLogger()->log(
					LogCategory::CACHE,
					LogPriority::ERROR,
					"File " + path + " is bigger than the cache"
				);

				delete asset;
			}
			else
			{
				// Make sure file fits in cache
				while (size + assetSize > maxSize)
					removeLeastRecentlyUsed();

				// Load file and insert it in the cache
				asset->load();
				cache.push_front(asset);
				assetMap.insert(std::pair<std::string, ObjectListIterator>(path, cache.begin()));

				size += assetSize;

				result = asset;
			}
		}
		else
		{
			delete asset;
		}
	}
	else
	{
		// The asset is already in cache, move it to the front and return it
		ObjectListIterator node = it->second;
		cache.splice(cache.begin(), cache, node);

		result = *node;
	}

	return result;
}
