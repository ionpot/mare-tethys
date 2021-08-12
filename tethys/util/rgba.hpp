#pragma once

#include "rgb.hpp"

#include <cstdint>

namespace tethys::util {
	struct RGBA {
		RGB channels;
		uint8_t alpha;

		RGBA(const RGB&, uint8_t a = 255);

		static const RGBA blank;

		static RGBA transparent(const RGB& rgb);
	};
}
