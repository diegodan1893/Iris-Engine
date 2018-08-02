#include "WaitForText.h"
#include "TextWindow.h"

WaitForText::WaitForText(TextWindow* textWindow)
	:textWindow(textWindow)
{
}

WaitForText::WaitForText(TextWindow* textWindow, const std::string& text)
	:textWindow(textWindow),
	 text(text)
{
}

WaitForText::WaitForText(TextWindow* textWindow, const std::string& name, const std::string& text)
	:textWindow(textWindow),
	 text(text),
	 name(name)
{
}

bool WaitForText::ready()
{
	if (!text.empty())
	{
		textWindow->setText(name, text);
		text.clear();
	}

	return textWindow->ready();
}
