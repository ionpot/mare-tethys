#include "hexagon.hpp"

#include "line.hpp"
#include "point.hpp"

#include <algorithm>
#include <cmath>

namespace tethys {
	const double sqrt3 = std::sqrt(3);

	int round(double d)
	{
		return static_cast<int>(std::lround(d));
	}

	Hexagon::Hexagon(double side):
		offset {
			Point {
				std::max(1, round(side / 2)),
				std::max(1, round(side / 2 * sqrt3))
			}
		},
		margin {1},
		side {round(side)}
	{
		if (side < 1)
			throw Exception {"Side length is less than 1."};
	}

	Point Hexagon::point1() const
	{
		return {offset.x, 0};
	}

	Point Hexagon::point2() const
	{
		return {offset.x + side - 1, 0};
	}

	Point Hexagon::point3() const
	{
		return {width() - 1, offset.y};
	}

	Point Hexagon::point4() const
	{
		return {offset.x + side - 1, height() - 1};
	}

	Point Hexagon::point5() const
	{
		return {offset.x, height() - 1};
	}

	Point Hexagon::point6() const
	{
		return {0, offset.y};
	}

	Size Hexagon::size() const
	{
		return {width(), height()};
	}

	int Hexagon::height() const
	{
		return offset.y * 2 + 1;
	}

	int Hexagon::width() const
	{
		return offset.x * 2 + side;
	}

	Point Hexagon::above() const
	{
		return {0, -margin - height()};
	}

	Point Hexagon::above_left() const
	{
		return {-offset.x - side - margin, offset.y - height() - margin};
	}

	Point Hexagon::above_right() const
	{
		return {offset.x + side + margin, offset.y - height() - margin};
	}
}
