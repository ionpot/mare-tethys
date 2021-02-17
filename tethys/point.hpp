#ifndef TETHYS_POINT_HPP
#define TETHYS_POINT_HPP

#include <SDL.h>

namespace tethys {
	struct Point {
		int x = 0;
		int y = 0;
		SDL_Point to_sdl() const
		{
			SDL_Point point;
			point.x = x;
			point.y = y;
			return point;
		}
	};
}

#endif
