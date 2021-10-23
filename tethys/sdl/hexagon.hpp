#pragma once

#include "point.hpp"
#include "size.hpp"

namespace tethys::sdl {
	struct Hexagon {
		int side;
		int x1, x2, x3;
		int y1, y2;
		Point center;

		Hexagon(double side);

		Size size() const;
		int height() const;
		int width() const;

		bool contains(Point) const;

		// clockwise from top left
		Point point1() const;
		Point point2() const;
		Point point3() const;
		Point point4() const;
		Point point5() const;
		Point point6() const;
	};
}
