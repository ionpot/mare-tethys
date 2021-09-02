#pragma once

#include "exception.hpp"
#include "file_line.hpp"

#include <cstdint>
#include <string>

#define TETHYS_INT(expr)\
	tethys::util::int_cast(expr, TETHYS_FILE_LINE(), #expr)

#define TETHYS_INT_INDEX(expr, max)\
	tethys::util::int_index(expr, max, TETHYS_FILE_LINE(), #expr)

#define TETHYS_INT_NATURAL(expr)\
	tethys::util::int_natural(expr, TETHYS_FILE_LINE(), #expr)

#define TETHYS_INT_POSITIVE(expr)\
	tethys::util::int_positive(expr, TETHYS_FILE_LINE(), #expr)

#define TETHYS_INT_ROUND(expr)\
	tethys::util::int_round(expr, TETHYS_FILE_LINE(), #expr)

#define TETHYS_INT_WITHIN(expr, max)\
	tethys::util::int_within(expr, max, TETHYS_FILE_LINE(), #expr)

#define TETHYS_UINT8(expr)\
	tethys::util::int_uint8(expr, TETHYS_FILE_LINE(), #expr)

namespace tethys::util {
	TETHYS_EXCEPTION_AS(IntException, "Integer")
	int int_cast(uintmax_t, FileLine location, std::string name);
	int int_index(int n, int max, FileLine location, std::string name);
	int int_natural(int, FileLine location, std::string name);
	int int_positive(int, FileLine location, std::string name);
	int int_round(double d, FileLine loc, std::string name);
	int int_within(int n, int max, FileLine location, std::string name);
	uint8_t int_uint8(uintmax_t, FileLine location, std::string name);
}
