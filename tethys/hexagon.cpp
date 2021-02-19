#include "hexagon.hpp"

#include "point.hpp"

#include <algorithm>
#include <cmath>

namespace tethys::s {
	const double sqrt3 = std::sqrt(3);

	int round(double d)
	{
		return static_cast<int>(std::lround(d));
	}

	int round1(double d)
	{
		return std::max(1, round(d));
	}
}

namespace tethys {
	Hexagon::Hexagon(double a_side):
		side {s::round(a_side)},
		x1 {s::round1(a_side / 2)},
		x2 {x1 + side - 1},
		x3 {x1 + x2},
		y1 {s::round1(a_side / 2 * s::sqrt3)},
		y2 {y1 * 2}
	{
		if (side < 1)
			throw Exception {"Side length is less than 1."};
	}

	Point Hexagon::point1() const
	{
		return {x1, 0};
	}

	Point Hexagon::point2() const
	{
		return {x2, 0};
	}

	Point Hexagon::point3() const
	{
		return {x3, y1};
	}

	Point Hexagon::point4() const
	{
		return {x2, y2};
	}

	Point Hexagon::point5() const
	{
		return {x1, y2};
	}

	Point Hexagon::point6() const
	{
		return {0, y1};
	}

	Size Hexagon::size() const
	{
		return {width(), height()};
	}

	int Hexagon::height() const
	{
		return y2 + 1;
	}

	int Hexagon::width() const
	{
		return x3 + 1;
	}

	Point Hexagon::above() const
	{
		return {0, -height() - 1};
	}

	Point Hexagon::above_left() const
	{
		return {-x2 - 2, -y1 - 1};
	}

	Point Hexagon::above_right() const
	{
		return {x2 + 2, -y1 - 1};
	}
}
