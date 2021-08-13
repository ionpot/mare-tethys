#include "rgb.hpp"

#include "exception.hpp"
#include "int.hpp"

#include <cstdint>
#include <string>

namespace tethys::util {
	namespace {
		int
		s_int(std::string hex)
		try {
			return std::stoi(hex, 0, 16);
		}
		catch (const std::invalid_argument&) {
			throw RGB::InvalidHex {hex};
		}

		uint8_t
		s_uint8(std::string hex)
		{
			return TETHYS_UINT8(s_int(hex));
		}

		RGB
		s_rgb(std::string hex)
		{
			switch (hex.size()) {
			case 1:
				return s_rgb(hex + hex);
			case 2:
				return s_rgb(hex + hex + hex);
			case 3: {
				auto red = hex.substr(0, 1);
				auto green = hex.substr(1, 1);
				auto blue = hex.substr(2, 1);
				return s_rgb(red + red + green + green + blue + blue);
			}
			case 6:
				return {
					s_uint8(hex.substr(0, 2)),
					s_uint8(hex.substr(2, 2)),
					s_uint8(hex.substr(4, 2))
				};
			default:
				throw RGB::InvalidHex {hex};
			}
		}
	}

	const RGB RGB::black {};
	const RGB RGB::white {255, 255, 255};

	RGB
	RGB::from_hex(std::string hex)
	try {
		return s_rgb(hex);
	}
	catch (const util::Exception&) {
		throw InvalidHex {hex};
	}
}
