#pragma once

#include <string>

/// <summary>
/// Holds a resource that can be cached such as
/// an image or a sound.
/// </summary>
class Asset
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Asset"/> class.
	/// </summary>
	/// <param name="path">The path to the file where the resource is located.</param>
	Asset(const std::string& path);
	virtual ~Asset() {}

	virtual const std::string& getPath() const;
	
	/// <summary>
	/// Gets the size of the stream that was used
	/// to create the asset in bytes.
	/// </summary>
	/// <returns>The size of the asset in bytes.</returns>
	virtual unsigned int getSize() const = 0;
	
	/// <summary>
	/// Determines whether this asset has been
	/// successfully loaded.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this asset has been loaded; otherwise, <c>false</c>.
	/// </returns>
	virtual bool isValid() const;
	
	/// <summary>
	/// Loads the asset from the file specified
	/// in the path. Use <see cref="isValid"/> to
	/// check if the load was successfull.
	/// </summary>
	virtual void load() = 0;

protected:
	bool valid;

private:
	std::string path;
};
