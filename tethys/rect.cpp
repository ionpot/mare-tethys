#include "rect.hpp"

#include "point.hpp"
#include "size.hpp"

#include <SDL.h>

namespace tethys {
	bool Rect::contains(Point p) const
	{
		auto rect = to_sdl();
		auto point = p.to_sdl();
		return SDL_PointInRect(&point, &rect) == SDL_TRUE;
	}

	SDL_Rect Rect::to_sdl() const
	{
		SDL_Rect rect;
		rect.x = position.x;
		rect.y = position.y;
		rect.w = size.width;
		rect.h = size.height;
		return rect;
	}
}
