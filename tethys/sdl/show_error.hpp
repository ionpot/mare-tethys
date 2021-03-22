#pragma once

#include <SDL.h>
#include <string>

namespace tethys::sdl {
	void show_error(const char* title, const char* text)
	{
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR,
			title, text,
			NULL
		);
	}
	void show_error(std::string title, std::string text)
	{
		show_error(title.c_str(), text.c_str());
	}
}
