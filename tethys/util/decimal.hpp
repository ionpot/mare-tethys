#pragma once

#include "string.hpp"

#include <cstdlib> // div
#include <string>

namespace tethys::util {
	template<int P> // P = powers of ten
	class Decimal {
	public:
		Decimal(double d):
			m_value {static_cast<int>(d * P)}
		{}

		Decimal(int i):
			m_value {i * P}
		{}

		operator std::string() const
		{
			auto [quot, rem] = std::div(m_value, P);
			auto integral = std::to_string(quot);
			auto fractional = string::trim_trailing_zeroes(std::to_string(rem));
			return fractional.empty()
				? integral
				: integral + "." + fractional;
		}

	private:
		int m_value;
	};
}
