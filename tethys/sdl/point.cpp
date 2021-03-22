#include "point.hpp"

#include "size.hpp"

#include <SDL.h>
#include <cmath>

namespace tethys::sdl {
	Point::Point():
		Point {0, 0}
	{}

	Point::Point(int x, int y):
		x {x}, y {y}
	{}

	Point::Point(Size size):
		x {size.width}, y {size.height}
	{}

	void
	Point::clear()
	{
		*this = {};
	}

	double
	Point::distance(Point target) const
	{
		Point p {target - *this};
		return std::sqrt(
			std::pow(p.x, 2) + std::pow(p.y, 2)
		);
	}

	Point
	Point::min(Point a, Point b)
	{
		a.pick_min(b);
		return a;
	}

	Point
	Point::max(Point a, Point b)
	{
		a.pick_max(b);
		return a;
	}

	Point
	Point::negate() const
	{
		return Point {0, 0} - Point {x, y};
	}

	void
	Point::pick_min(const Point& p)
	{
		if (p.x < x)
			x = p.x;
		if (p.y < y)
			y = p.y;
	}

	void
	Point::pick_max(const Point& p)
	{
		if (p.x > x)
			x = p.x;
		if (p.y > y)
			y = p.y;
	}

	SDL_Point
	Point::to_sdl() const
	{
		SDL_Point point;
		point.x = x;
		point.y = y;
		return point;
	}

	Point
	Point::operator+(const Point& p) const
	{
		return {x + p.x, y + p.y};
	}

	Point
	Point::operator-(const Point& p) const
	{
		return {x - p.x, y - p.y};
	}

	Point&
	Point::operator+=(const Point& p)
	{
		*this = *this + p;
		return *this;
	}

	Point&
	Point::operator-=(const Point& p)
	{
		*this = *this - p;
		return *this;
	}

	bool
	Point::operator==(const Point& p) const
	{
		return (x == p.x) && (y == p.y);
	}

	bool
	Point::operator!=(const Point& p) const
	{
		return (x != p.x) || (y != p.y);
	}
}
