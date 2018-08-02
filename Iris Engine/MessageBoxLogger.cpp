#include "MessageBoxLogger.h"

#include <SDL.h>

void MessageBoxLogger::log(LogCategory category, LogPriority priority, std::string text)
{
	switch (priority)
	{
	case LogPriority::INFO:
		// Log as text
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, text.c_str());
		break;

	case LogPriority::WARNING:
		// Log as text
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, text.c_str());

		// Show a message box
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, u8"Warning", text.c_str(), nullptr);
		break;

	case LogPriority::ERROR:
		// Log as text
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, text.c_str());

		// Show a message box
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"Error", text.c_str(), nullptr);
		break;
	}
}
