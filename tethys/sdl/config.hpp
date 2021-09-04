#pragma once

#include "context.hpp"
#include "font.hpp"
#include "size.hpp"
#include "text_box.hpp"

#include <util/cfg_file.hpp>

#include <string>

namespace tethys::sdl {
	struct Config {
		struct Font {
			std::string file;
			int size;
			Font(const util::CfgFile::Section&);
			sdl::Font create(const Context&) const;
		};
		Font font;
		double hex_side;
		int scroll_speed;
		TextBox::Config text_box;
		Size window_size;

		Config(const util::CfgFile&);
	};
}
