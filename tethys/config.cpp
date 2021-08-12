#include "config.hpp"

#include <sdl/point.hpp>
#include <sdl/size.hpp>

#include <ui/box.hpp>
#include <ui/text_box.hpp>

#include <util/cfg_file.hpp>
#include <util/rgb.hpp>

namespace tethys {
	namespace {
		sdl::Point
		s_point(const util::CfgFile::Pair& pair)
		{
			auto [a, b] = pair.to_int_pair();
			return {a, b};
		}

		util::RGB
		s_rgb(const util::CfgFile::Pair& pair)
		{
			return util::RGB::from_hex(pair.value);
		}

		ui::TextBox::Config
		s_text_box(const util::CfgFile& file)
		{
			auto section = file.find_section("text box");
			return {
				ui::Box::Config {
					s_rgb(section.find_pair("background color")),
					s_rgb(section.find_pair("border color")),
					section.find_pair("border width").to_int()
				},
				s_point(section.find_pair("padding")),
				s_rgb(section.find_pair("text color"))
			};
		}

		sdl::Size
		s_window_size(const util::CfgFile& file)
		{
			auto section = file.find_section("window");
			return {
				section.find_pair("width").to_int(),
				section.find_pair("height").to_int()
			};
		}
	}

	Config::Font::Font(const util::CfgFile::Section& section):
		file {section.find_pair("file").value},
		size {section.find_pair("size").to_int()}
	{}

	Config::Hex::Hex(const util::CfgFile::Section& section):
		gold {section.find_pair("gold").to_double()},
		industry {section.find_pair("industry").to_double()},
		manpower {section.find_pair("manpower").to_double()}
	{}

	Config::Config(const util::CfgFile& file):
		city {file.find_section("city hex")},
		forest {file.find_section("forest hex")},
		mountain {file.find_section("mountain hex")},
		plains {file.find_section("plains hex")},
		sea {file.find_section("sea hex")},
		gold_per_trade {file.find_pair("gold per trade").to_double()},
		trade_value {file.find_pair("trade value").to_double()},
		hex_side {file.find_pair("hex side").to_double()},
		font {file.find_section("font")},
		scroll_speed {file.find_pair("scroll speed").to_int()},
		text_box {s_text_box(file)},
		window_size {s_window_size(file)}
	{}
}
