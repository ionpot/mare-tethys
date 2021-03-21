#pragma once

#include "point.hpp"
#include "size.hpp"

#include <SDL.h>

namespace tethys::sdl {
	struct Rect {
		Point position;
		Size size;
		Rect(Size);
		Rect(Point, Size);
		bool contains(Point) const;
		SDL_Rect to_sdl() const;
	};
}
