#include "int.hpp"

#include "file_line.hpp"

#include <climits>
#include <cmath>
#include <cstdint>
#include <string>

namespace tethys::util {
	namespace {
		template<typename T>
		std::string
		s_eq(std::string name, T value)
		{
			return name + " = " + std::to_string(value);
		}

		std::string
		s_location(FileLine location)
		{
			return "(in " + location.to_string() + ")";
		}

		std::string
		s_quote(std::string str)
		{
			return "\"" + str + "\"";
		}
	}

	int
	int_cast(uintmax_t number, FileLine loc, std::string name)
	{
		if (number > INT_MAX)
			throw IntException {
				s_quote(name) + " too large for int "
				+ s_location(loc) + "."
			};
		return (int)number;
	}

	int
	int_index(int number, int max, FileLine loc, std::string name)
	{
		int_natural(number, loc, name);
		if (number < max)
			return number;
		throw IntException {
			s_quote(s_eq(name, number))
			+ " is not a valid index for " + std::to_string(max)
			+ " " + s_location(loc) + "."
		};
	}

	int
	int_natural(int number, FileLine loc, std::string name)
	{
		if (number >= 0)
			return number;
		throw IntException {
			s_quote(s_eq(name, number))
			+ " must not have a negative value "
			+ s_location(loc) + "."
		};
	}

	int
	int_positive(int number, FileLine loc, std::string name)
	{
		if (number > 0)
			return number;
		throw IntException {
			s_quote(s_eq(name, number))
			+ " must have a positive value "
			+ s_location(loc) + "."
		};
	}

	int
	int_round(double d, FileLine loc, std::string name)
	{
		long x {std::lround(d)};
		if (INT_MIN <= x || x <= INT_MAX)
			return (int)x;
		throw IntException {
			s_quote(s_eq(name, d))
			+ " does not fit in an int "
			+ s_location(loc) + "."
		};
	}

	int
	int_within(int number, int max, FileLine loc, std::string name)
	{
		if (number <= max)
			return number;
		throw IntException {
			s_quote(s_eq(name, number))
			+ " is not within " + std::to_string(max)
			+ " " + s_location(loc) + "."
		};
	}

	uint8_t
	int_uint8(uintmax_t number, FileLine loc, std::string name)
	{
		if (number <= UCHAR_MAX)
			return (uint8_t)number;
		throw IntException {
			s_quote(s_eq(name, number))
			+ " is larger than " + std::to_string(UCHAR_MAX)
			+ " " + s_location(loc) + "."
		};
	}
}
