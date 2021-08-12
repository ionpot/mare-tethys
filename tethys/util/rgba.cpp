#include "rgba.hpp"

#include "rgb.hpp"

#include <cstdint>

namespace tethys::util {
	const RGBA RGBA::blank {RGB::black, 0};

	RGBA::RGBA(const RGB& rgb, uint8_t a):
		channels {rgb},
		alpha {a}
	{}

	RGBA
	RGBA::transparent(const RGB& rgb)
	{ return {rgb, 0}; }
}
