#include "grid_file.hpp"

#include "file.hpp"
#include "hex_type.hpp"

#include <string>
#include <vector>

namespace tethys::s {
	HexType
	get_type(char ch, int row_num)
	{
		switch (ch) {
		case 'c':
			return HexType::city;
		case 'd':
			return HexType::desert;
		case 'f':
			return HexType::forest;
		case 'm':
			return HexType::mountain;
		case 'p':
			return HexType::plains;
		case 's':
			return HexType::sea;
		case 'x':
			return HexType::none;
		default:
			throw GridFile::Exception {
				"Unrecognised character '" + std::string {ch}
				+ "' on row " + std::to_string(row_num) + "."
			};
		}
	}
}

namespace tethys {
	GridFile
	GridFile::read(std::string filename)
	{
		GridFile grid;
		auto lines = file::read_lines(filename);
		grid.rows = lines.size();
		if (grid.rows > 0) {
			grid.columns = lines.front().size();
		}
		int row_number {1};
		for (const auto& line : lines) {
			int cols = line.size();
			if (cols != grid.columns)
				throw Exception {
					"Row " + std::to_string(row_number)
					+ " must have " + std::to_string(grid.columns)
					+ " characters."
				};
			for (const auto& ch : line) {
				auto type = s::get_type(ch, row_number);
				grid.types.push_back(type);
			}
			++row_number;
		}
		return grid;
	}
}
