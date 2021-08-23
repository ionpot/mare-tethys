#include "surface.hpp"

#include <SDL.h>

namespace tethys::sdl {
	Surface::Surface(SDL_Surface* ptr):
		pointer {ptr}
	{}

	Surface::~Surface()
	{
		if (pointer) {
			SDL_FreeSurface(pointer);
			pointer = NULL;
		}
	}

	Surface::Surface(Surface&& from) noexcept:
		pointer {from.pointer}
	{
		from.pointer = NULL;
	}

	Surface&
	Surface::operator=(Surface&& from) noexcept
	{
		pointer = from.pointer;
		from.pointer = NULL;
		return *this;
	}
}
