#pragma once

#include "font.hpp"
#include "size.hpp"
#include "text_box.hpp"

#include <util/cfg_file.hpp>

#include <string>

namespace tethys::sdl {
	struct Config {
		Font::Config font;
		double hex_side;
		int scroll_speed;
		TextBox::Config text_box;
		Size window_size;

		Config(const util::CfgFile&);
	};
}
