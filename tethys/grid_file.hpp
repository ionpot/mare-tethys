#pragma once

#include <game/grid.hpp>

#include <util/exception.hpp>

#include <string>

namespace tethys::grid_file {
	struct Exception : public util::Exception {
		Exception(std::string text):
			util::Exception {"GridFile", text}
		{}
	};
	game::Grid read(std::string filename);
}
