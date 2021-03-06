#ifndef TETHYS_POINT_HPP
#define TETHYS_POINT_HPP

#include "size.hpp"

#include <SDL.h>
#include <cmath>

namespace tethys {
	struct Point {
		int x = 0;
		int y = 0;
		Point():
			Point {0, 0}
		{}
		Point(int x, int y):
			x {x}, y {y}
		{}
		Point(Size size):
			x {size.width}, y {size.height}
		{}
		static Point min(Point a, Point b = {0, 0})
		{
			a.pick_min(b);
			return a;
		}
		static Point max(Point a, Point b = {0, 0})
		{
			a.pick_max(b);
			return a;
		}
		void clear()
		{
			*this = {};
		}
		double distance(Point target) const
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
		Point& operator-=(const Point& p)
		{
			*this = *this - p;
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
