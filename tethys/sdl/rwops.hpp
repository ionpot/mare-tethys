#pragma once

#include <util/macros.hpp>

#include <SDL.h>

namespace tethys::sdl {
	class RWops {
	public:
		SDL_RWops* pointer;

		~RWops();
		TETHYS_NO_COPY(RWops)
		TETHYS_DECLARE_MOVE(RWops)

	private:
		friend class Base;
		RWops(SDL_RWops*);
	};
}
