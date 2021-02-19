#ifndef TETHYS_HEXAGON_HPP
#define TETHYS_HEXAGON_HPP

#include "exception.hpp"
#include "point.hpp"
#include "size.hpp"

#include <string>

namespace tethys {
	struct Hexagon {
		struct Exception : public tethys::Exception {
			Exception(const std::string text):
				tethys::Exception {"Hexagon", text}
			{}
		};
		const int side;
		const int x1, x2, x3;
		const int y1, y2;
		Hexagon(double side);
		Point point1() const;
		Point point2() const;
		Point point3() const;
		Point point4() const;
		Point point5() const;
		Point point6() const;
		Size size() const;
		int height() const;
		int width() const;

		// neighbour points
		Point above() const;
		Point above_left() const;
		Point above_right() const;
	};
}

#endif
