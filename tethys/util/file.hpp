#pragma once

#include "exception.hpp"

#include <fstream>
#include <list>
#include <string>

namespace tethys::util::file {
	typedef std::list<std::string> LineList;

	struct Exception : public util::Exception {
		Exception(std::string text):
			util::Exception {"File", text}
		{};
	};

	struct OpenFailed : public Exception {
		OpenFailed(std::string filename);
	};

	std::ofstream open_w(std::string filename);

	LineList read_lines(std::string filename);
}
