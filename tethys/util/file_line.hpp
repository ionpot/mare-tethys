#pragma once

#include "macros.hpp"

#include <string>
#include <sstream>

#define TETHYS_FILE_LINE()\
	tethys::util::FileLine {TETHYS_FILE, __LINE__}

namespace tethys::util {
	struct FileLine {
		char* file;
		int line;
		std::string to_string() const
		{
			std::stringstream ss;
			ss << file << ":" << line;
			return ss.str();
		}
	};
}
