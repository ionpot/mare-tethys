#pragma once

#include "font.hpp"

#include <util/log.hpp>
#include <util/macros.hpp>

namespace tethys::sdl {
	struct Ttf {
		static bool was_init();

		Ttf(util::Log& log);
		~Ttf();
		TETHYS_NO_COPY(Ttf)

		Font load_font(Font::Config) const;
	};
}
