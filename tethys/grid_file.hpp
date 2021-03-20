#ifndef TETHYS_GRID_FILE_HPP
#define TETHYS_GRID_FILE_HPP

#include "hex_type.hpp"

#include <util/exception.hpp>

#include <string>
#include <vector>

namespace tethys {
	struct GridFile {
		struct Exception : public tethys::Exception {
			Exception(std::string text):
				tethys::Exception {"GridFile", text}
			{}
		};
		int rows;
		int columns;
		std::vector<HexType> types;
		static GridFile read(std::string filename);
	};
}

#endif
