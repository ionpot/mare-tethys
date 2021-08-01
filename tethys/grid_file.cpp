#include "grid_file.hpp"

#include <game/grid.hpp>
#include <game/hex_type.hpp>

#include <util/file.hpp>
#include <util/grid.hpp>
#include <util/int.hpp>

#include <string>

namespace tethys::grid_file {
	namespace {
		char
		s_char_at(int i, const std::string& line)
		{
			return (i < TETHYS_INT(line.size())) ? line[i] : 'x';
		}

		game::HexType
		s_get_type(char ch)
		{
			switch (ch) {
			case 'a':
				return game::HexType::agriculture;
			case 'c':
				return game::HexType::city;
			case 'd':
				return game::HexType::desert;
			case 'f':
				return game::HexType::forest;
			case 'h':
				return game::HexType::hills;
			case 'm':
				return game::HexType::mountain;
			case 'p':
				return game::HexType::plains;
			case 's':
				return game::HexType::sea;
			case 'x':
				return game::HexType::none;
			case 'v':
				return game::HexType::village;
			default:
				throw Exception {
					"Unrecognised character: " + std::string {ch}
				};
			}
		}

		util::GridSize
		s_grid_size_of(const util::file::LineList& lines)
		{
			util::GridSize size;
			for (const auto& line : lines) {
				auto len = TETHYS_INT(line.size());
				if (len > 0) {
					++size.rows;
					if (len > size.columns)
						size.columns = len;
				}
			}
			return size;
		}

		std::string
		s_index_to_str(util::GridIndex i)
		{
			return "row " + std::to_string(i.row + 1)
				+ ", column " + std::to_string(i.column + 1);
		}
	}

	game::Grid
	read(std::string filename)
	{
		const auto lines = util::file::read_lines(filename);
		util::GridIndex index;
		util::GridSize size {s_grid_size_of(lines)};
		game::Grid grid {size};
		for (const auto& line : lines) {
			if (line.empty())
				continue;
			auto& i = index.column;
			for (i = 0; i < size.columns; i++) {
				auto ch = s_char_at(i, line);
				try {
					auto type = s_get_type(ch);
					grid.cell(index, type);
				}
				catch (const Exception& ex) {
					throw Exception {
						"Error at " + s_index_to_str(index) + ": " + ex.text
					};
				}
			}
			++index.row;
		}
		return grid;
	}
}
