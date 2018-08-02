#pragma once

#include "Vector.h"
#include <string>

struct FontProperties
{
	std::string fontFile;
	int fontSize;
	Color fontColor;
	int shadowDistance;
	Color shadowColor;

	FontProperties() {}
	FontProperties(const std::string& fontFile, int fontSize, const Color& fontColor, int shadowDistance, const Color& shadowColor)
		:fontFile(fontFile),
		 fontSize(fontSize),
		 fontColor(fontColor),
		 shadowDistance(shadowDistance),
		 shadowColor(shadowColor)
	{
	}
};