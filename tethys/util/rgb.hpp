#pragma once

#include "exception.hpp"

#include <cstdint>
#include <string>

namespace tethys::util {
	struct RGB {
		TETHYS_EXCEPTION("RGB")

		struct InvalidHex : public Exception {
			InvalidHex(std::string hex):
				Exception {"Invalid hex code: " + hex}
			{}
		};

		uint8_t red {0};
		uint8_t green {0};
		uint8_t blue {0};

		static const RGB black;
		static const RGB white;

		static RGB from_hex(std::string hex);
	};
}
