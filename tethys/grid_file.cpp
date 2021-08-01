#include "grid_file.hpp"

#include <game/grid.hpp>
#include <game/hex_type.hpp>

#include <util/file.hpp>
#include <util/grid.hpp>
#include <util/int.hpp>

#include <string>

namespace tethys::grid_file {
	namespace {
		const int s_token_length = 3;

		game::HexType
		s_get_type(std::string token)
		{
			if (token == "agr")
				return game::HexType::agriculture;
			if (token == "cit")
				return game::HexType::city;
			if (token == "des")
				return game::HexType::desert;
			if (token == "for")
				return game::HexType::forest;
			if (token == "hil")
				return game::HexType::hills;
			if (token == "mou")
				return game::HexType::mountain;
			if (token == "pla")
				return game::HexType::plains;
			if (token == "sea")
				return game::HexType::sea;
			if (token == "vil")
				return game::HexType::village;
			if (token == "---")
				return game::HexType::none;

			throw Exception {"Unrecognised character: " + token};
		}

		util::GridSize
		s_grid_size_of(const util::file::LineList& lines)
		{
			util::GridSize size;
			auto step = s_token_length + 1;
			for (const auto& line : lines) {
				auto len = TETHYS_INT(line.size());
				if (len > 0) {
					++size.rows;
					auto cols = (len + 1) / step;
					if (cols > size.columns)
						size.columns = cols;
				}
			}
			return size;
		}
	}

	game::Grid
	read(std::string filename)
	{
		const auto lines = util::file::read_lines(filename);
		util::GridSize size {s_grid_size_of(lines)};
		game::Grid grid {size};
		auto iter = grid.begin();
		auto step = s_token_length + 1;
		for (const auto& line : lines) {
			if (line.empty())
				continue;
			auto len = TETHYS_INT(line.length());
			for (auto pos = 0; pos < len; pos += step) {
				auto token = line.substr(pos, s_token_length);
				auto type = s_get_type(token);
				grid.cell(iter.index(), type);
				iter.next();
			}
			if (!iter.at_new_row())
				iter.next_row();
		}
		return grid;
	}
}
