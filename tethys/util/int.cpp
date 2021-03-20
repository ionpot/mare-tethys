#include "int.hpp"

#include "exception.hpp"
#include "file_line.hpp"

#include <climits>
#include <cstdint>
#include <string>

namespace tethys::util {
	int
	int_cast(uintmax_t number, FileLine location, std::string name)
	{
		if (number > INT_MAX)
			throw IntException {
				"\"" + name + "\" too large for int"
				+ " (in " + location.to_string() + ")."
			};
		return (int)number;
	}
}
