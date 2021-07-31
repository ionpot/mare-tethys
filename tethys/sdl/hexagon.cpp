#include "hexagon.hpp"

#include "point.hpp"

#include <util/int.hpp>

#include <algorithm>
#include <cmath>

namespace tethys::sdl {
	namespace {
		const double s_sqrt3 = std::sqrt(3);

		int s_round(double d)
		{
			return static_cast<int>(std::lround(d));
		}

		int s_round1(double d)
		{
			return std::max(1, s_round(d));
		}
	}

	Hexagon::Hexagon(double a_side):
		side {TETHYS_INT_POSITIVE(s_round(a_side))},
		x1 {s_round1(a_side / 2)},
		x2 {x1 + side - 1},
		x3 {x1 + x2},
		y1 {s_round1(a_side / 2 * s_sqrt3)},
		y2 {y1 * 2},
		center {(x3 + 1) / 2, (y2 + 1) / 2}
	{
	}

	bool Hexagon::contains(Point p) const
	{
		auto r = static_cast<double>(center.x);
		return p.distance(center) <= r;
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
}
