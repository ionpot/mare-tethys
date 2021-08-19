#pragma once

#include <sdl/context.hpp>
#include <sdl/size.hpp>
#include <sdl/text_box.hpp>

#include <util/cfg_file.hpp>

#include <string>

namespace tethys::ui {
	struct Config {
		struct Font {
			std::string file;
			int size;
			Font(const util::CfgFile::Section&);
			sdl::Font create(const sdl::Context&) const;
		};
		Font font;
		double hex_side;
		int scroll_speed;
		sdl::TextBox::Config text_box;
		sdl::Size window_size;

		Config(const util::CfgFile&);
	};
}
