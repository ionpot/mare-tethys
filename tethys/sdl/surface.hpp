#pragma once

#include <util/macros.hpp>

#include <SDL.h>

namespace tethys::sdl {
	struct Surface {
		SDL_Surface* pointer;

		Surface(SDL_Surface*);
		~Surface();
		TETHYS_NO_COPY(Surface)
		TETHYS_DECLARE_MOVE(Surface)

		bool is_null() const;
	};
}
