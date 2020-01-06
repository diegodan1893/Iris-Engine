#include "StringConverter.h"

#include <codecvt>

std::u16string StringConverter::convertToUTF16(const std::string & string)
{
	//std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;

	// Workaround for VS 2015 bug https://goo.gl/WZ7YQp
	std::wstring_convert<std::codecvt_utf8_utf16<uint16_t>, uint16_t> convert;

	return (char16_t*)convert.from_bytes(string).c_str();
}
