#pragma once

#include "hexagon.hpp"
#include "point.hpp"
#include "size.hpp"

#include <util/grid.hpp>

namespace tethys::sdl {
	struct HexGrid {
		Hexagon hex;

		HexGrid(Hexagon);

		bool contains(Point, util::GridIndex) const;

		util::GridIndex get_visible_index(Point) const;
		int get_visible_column(int x_pos) const;
		int get_visible_row(int y_pos) const;

		util::GridSize max_visible(Size) const;
		int max_visible_columns(int size) const;
		int max_visible_rows(int size) const;

		Point position_of(util::GridIndex) const;
		int x_of(util::GridIndex) const;
		int y_of(util::GridIndex) const;

		Size size_of(util::GridSize) const;

		static Size calculate_size(const Hexagon&, util::GridSize);
		static int calculate_height(const Hexagon&, util::GridSize);
		static int calculate_width(const Hexagon&, util::GridSize);
	};
}
