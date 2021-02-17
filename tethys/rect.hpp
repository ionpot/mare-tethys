#ifndef TETHYS_RECT_HPP
#define TETHYS_RECT_HPP

#include "point.hpp"
#include "size.hpp"

#include <SDL.h>

namespace tethys {
	struct Rect {
		Point position;
		Size size;
		bool contains(Point) const;
		SDL_Rect to_sdl() const;
	};
}

#endif
