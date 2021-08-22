#pragma once

#include "surface.hpp"

#include <util/log.hpp>
#include <util/macros.hpp>

#include <string>

namespace tethys::sdl {
	struct Img {
		static int init_flags;
		static bool was_init;

		Img(util::Log& log);
		~Img();
		TETHYS_NO_COPY(Img)

		Surface load_png(std::string file) const;
	};
}
