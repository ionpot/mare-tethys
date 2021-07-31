#include "hex_grid.hpp"

#include "hexagon.hpp"
#include "point.hpp"
#include "size.hpp"

#include <util/int.hpp>
#include <util/grid.hpp>

namespace tethys::sdl {
	HexGrid::HexGrid(Hexagon hex):
		hex {hex}
	{}

	int
	HexGrid::calculate_height(const Hexagon& hex, util::GridSize size)
	{
		auto rows = TETHYS_INT_POSITIVE(size.rows);
		auto columns = TETHYS_INT_POSITIVE(size.columns);
		int offset {(columns > 1) ? hex.y1 : 0};
		return rows * hex.y2 + 1 + offset;
	}

	Size
	HexGrid::calculate_size(const Hexagon& hex, util::GridSize size)
	{
		return {
			calculate_width(hex, size),
			calculate_height(hex, size)
		};
	}

	int
	HexGrid::calculate_width(const Hexagon& hex, util::GridSize size)
	{
		auto columns = TETHYS_INT_POSITIVE(size.columns);
		return columns * hex.x2 + 1 + hex.x1;
	}

	bool
	HexGrid::contains(Point pos, util::GridIndex index) const
	{
		return hex.contains(pos - position_of(index));
	}

	int
	HexGrid::get_visible_column(int x_pos) const
	{
		auto base = hex.x1;
		if (x_pos < base)
			return 0;
		return (x_pos - base) / hex.x2;
	}

	util::GridIndex
	HexGrid::get_visible_index(Point pos) const
	{
		return {
			get_visible_row(pos.y),
			get_visible_column(pos.x)
		};
	}

	int
	HexGrid::get_visible_row(int y_pos) const
	{
		auto base = hex.y1;
		if (y_pos < base)
			return 0;
		return (y_pos - base) / hex.y2;
	}

	util::GridSize
	HexGrid::max_visible(Size size) const
	{
		return {
			max_visible_rows(size.height),
			max_visible_columns(size.width)
		};
	}

	int
	HexGrid::max_visible_columns(int size) const
	{
		if (size <= 0)
			return 0;
		auto a = hex.x1;
		auto ab = hex.x2;
		auto b = ab - a;
		auto base = b + 2;
		if (size < base)
			return 2;
		auto n = (size - base) / ab;
		return 3 + n;
	}

	int
	HexGrid::max_visible_rows(int size) const
	{
		if (size <= 0)
			return 0;
		auto h = hex.y2;
		auto base = h + 2;
		if (size < base)
			return 2;
		auto n = (size - base) / h;
		return 3 + n;
	}

	Point
	HexGrid::position_of(util::GridIndex index) const
	{
		return {x_of(index), y_of(index)};
	}

	Size
	HexGrid::size_of(util::GridSize s) const
	{
		return calculate_size(hex, s);
	}

	int
	HexGrid::x_of(util::GridIndex index) const
	{
		return index.column * hex.x2;
	}

	int
	HexGrid::y_of(util::GridIndex index) const
	{
		int y {index.row * hex.y2};
		if (index.column & 1)
			y += hex.y1;
		return y;
	}
}
