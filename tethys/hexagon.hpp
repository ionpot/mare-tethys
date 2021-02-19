#ifndef TETHYS_HEXAGON_HPP
#define TETHYS_HEXAGON_HPP

#include "exception.hpp"
#include "line.hpp"
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
		Point offset;
		int margin;
		int side;
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
