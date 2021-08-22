#include "config.hpp"

#include <sdl/box.hpp>
#include <sdl/point.hpp>
#include <sdl/size.hpp>
#include <sdl/text_box.hpp>

#include <util/cfg_file.hpp>
#include <util/rgb.hpp>

namespace tethys::ui {
	namespace {
		typedef util::CfgFile::Pair Pair;
		typedef util::CfgFile::Section Section;

		sdl::Point
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

		sdl::Size
		s_size(const Section& section)
		{
			return {
				section.find_pair("width").to_int(),
				section.find_pair("height").to_int()
			};
		}

		sdl::TextBox::Config
		s_text_box(const Section& section)
		{
			return {
				sdl::Box::Config {
					s_rgb(section.find_pair("background color")),
					s_rgb(section.find_pair("border color")),
					section.find_pair("border width").to_int(),
					s_point(section.find_pair("padding"))
				},
				s_rgb(section.find_pair("text color"))
			};
		}
	}

	Config::Font::Font(const Section& section):
		file {section.find_pair("file").value},
		size {section.find_pair("size").to_int()}
	{}

	sdl::Font
	Config::Font::create(const sdl::Context& ctx) const
	{
		return ctx.ttf.load_font(TETHYS_ASSETS_DIR "/" + file, size);
	}

	Config::Config(const util::CfgFile& file):
		font {file.find_section("font")},
		hex_side {file.find_pair("hex side").to_double()},
		scroll_speed {file.find_pair("scroll speed").to_int()},
		text_box {s_text_box(file.find_section("text box"))},
		window_size {s_size(file.find_section("window"))}
	{}
}
