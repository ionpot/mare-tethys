#pragma once

#include <sdl/size.hpp>
#include <ui/text_box.hpp>
#include <util/cfg_file.hpp>

#include <string>

namespace tethys {
	struct Config {
		struct Font {
			std::string file;
			int size;
			Font(const util::CfgFile::Section&);
		};
		struct Hex {
			double gold;
			double industry;
			double manpower;
			Hex(const util::CfgFile::Section&);
		};

		Hex city;
		Hex forest;
		Hex mountain;
		Hex plains;
		Hex sea;

		double gold_per_trade;
		double trade_value;

		double hex_side;

		Font font;

		int scroll_speed;

		ui::TextBox::Config text_box;

		sdl::Size window_size;

		Config(const util::CfgFile&);
	};
}
