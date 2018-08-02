#include "Asset.h"

Asset::Asset(const std::string& path)
	:path(path)
{
}

const std::string& Asset::getPath() const
{
	return path;
}

bool Asset::isValid() const
{
	return valid;
}
