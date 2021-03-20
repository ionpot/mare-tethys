#ifndef TETHYS_HEXAGON_HPP
#define TETHYS_HEXAGON_HPP

#include "point.hpp"
#include "size.hpp"

#include <util/exception.hpp>

#include <string>

namespace tethys::sdl {
	struct Hexagon {
		struct Exception : public util::Exception {
			Exception(std::string text):
				util::Exception {"Hexagon", text}
			{}
		};
		const int side;
		const int x1, x2, x3;
		const int y1, y2;
		const Point center;

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

		// neighbour points
		Point above() const;
		Point above_left() const;
		Point above_right() const;
		Point below() const;
		Point below_left() const;
		Point below_right() const;
	};
}

#endif
