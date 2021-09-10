#include "config.hpp"

#include "box.hpp"
#include "font.hpp"
#include "point.hpp"
#include "size.hpp"
#include "text_box.hpp"

#include <util/cfg_file.hpp>
#include <util/rgb.hpp>

namespace tethys::sdl {
	namespace {
		typedef util::CfgFile::Pair Pair;
		typedef util::CfgFile::Section Section;

		Font::Config
		s_font(const Section& section)
		{
			return {
				section.find_pair("file").value,
				section.find_pair("size").to_int()
			};
		}

		Point
		s_point(const Pair& pair)
		{
			auto [a, b] = pair.to_int_pair();
			return {a, b};
		}

		util::RGB
		s_rgb(const Pair& pair)
		{
			return util::RGB::from_hex(pair.value);
		}

		Size
		s_size(const Section& section)
		{
			return {
				section.find_pair("width").to_int(),
				section.find_pair("height").to_int()
			};
		}

		TextBox::Config
		s_text_box(const Section& section)
		{
			return {
				Box::Config {
					s_rgb(section.find_pair("background color")),
					s_rgb(section.find_pair("border color")),
					section.find_pair("border width").to_int(),
					s_point(section.find_pair("padding"))
				},
				s_rgb(section.find_pair("text color"))
			};
		}
	}

	Config::Config(const util::CfgFile& file):
		font {s_font(file.find_section("font"))},
		hex_side {file.find_pair("hex side").to_double()},
		scroll_speed {file.find_pair("scroll speed").to_int()},
		text_box {s_text_box(file.find_section("text box"))},
		window_size {s_size(file.find_section("window"))}
	{}
}
