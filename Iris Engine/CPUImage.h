#pragma once

#include "Asset.h"

/// <summary>
/// Holds an image asset that can be accessed
/// efficiently by the CPU
/// </summary>
/// <seealso cref="Asset" />
class CPUImage : public Asset
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="CPUImage"/> class.
	/// </summary>
	/// <param name="path">The path.</param>
	CPUImage(const std::string& path);
	virtual ~CPUImage();
	
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
	/// Gets the image.
	/// </summary>
	/// <returns>The loaded surface.</returns>
	struct SDL_Surface* getImage() const;

private:
	unsigned int size;
	struct SDL_RWops* stream;
	struct SDL_Surface* img;
};