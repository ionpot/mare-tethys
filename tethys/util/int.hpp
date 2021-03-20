#ifndef TETHYS_UTIL_INT_HPP
#define TETHYS_UTIL_INT_HPP

#include "exception.hpp"
#include "file_line.hpp"

#include <cstdint>
#include <string>

#define TETHYS_INT(expr)\
	tethys::int_cast(expr, TETHYS_FILE_LINE(), #expr)

namespace tethys {
	struct IntException : public Exception {
		IntException(std::string text):
			Exception {"Integer", text}
		{}
	};
	int int_cast(uintmax_t, FileLine location, std::string name);
}

#endif
