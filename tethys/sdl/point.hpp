#pragma once

#include "size.hpp"

#include <SDL.h>

namespace tethys::sdl {
	struct Point {
		int x = 0;
		int y = 0;
		Point();
		Point(int x, int y);
		Point(Size size);
		void clear();
		double distance(Point target) const;
		Point negate() const;
		void pick_min(const Point& p);
		void pick_max(const Point& p);
		SDL_Point to_sdl() const;
		Point operator+(const Point& p) const;
		Point operator-(const Point& p) const;
		Point& operator+=(const Point& p);
		Point& operator-=(const Point& p);
		bool operator==(const Point& p) const;
		bool operator!=(const Point& p) const;
		static Point min(Point a, Point b = {0, 0});
		static Point max(Point a, Point b = {0, 0});
	};
}
