#ifndef TETHYS_FILE_LINE_HPP
#define TETHYS_FILE_LINE_HPP

#include "macros.hpp"

#include <string>
#include <sstream>

#define TETHYS_FILE_LINE()\
	tethys::FileLine {TETHYS_FILE, __LINE__}

namespace tethys {
	struct FileLine {
		const char* file;
		int line;
		std::string to_string() const
		{
			std::stringstream ss;
			ss << file << ":" << line;
			return ss.str();
		}
	};
}

#endif
