#ifndef TETHYS_POINT_HPP
#define TETHYS_POINT_HPP

#include <SDL.h>
#include <cmath>

namespace tethys {
	struct Point {
		int x = 0;
		int y = 0;
		double distance(Point target)
		{
			Point p {target - *this};
			return std::sqrt(
				std::pow(p.x, 2) + std::pow(p.y, 2)
			);
		}
		void pick_min(const Point& p)
		{
			if (p.x < x)
				x = p.x;
			if (p.y < y)
				y = p.y;
		}
		void pick_max(const Point& p)
		{
			if (p.x > x)
				x = p.x;
			if (p.y > y)
				y = p.y;
		}
		Point negate() const
		{
			return Point {0, 0} - Point {x, y};
		}
		Point operator+(const Point& p) const
		{
			return {x + p.x, y + p.y};
		}
		Point operator-(const Point& p) const
		{
			return {x - p.x, y - p.y};
		}
		Point& operator+=(const Point& p)
		{
			*this = *this + p;
			return *this;
		}
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
