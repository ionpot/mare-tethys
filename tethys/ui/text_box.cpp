#include "text_box.hpp"

#include <sdl/font.hpp>
#include <sdl/point.hpp>
#include <sdl/renderer.hpp>
#include <sdl/size.hpp>

#include <string>

namespace tethys::ui {
	TextBox::TextBox(
			const TextBox::Config& config,
			const sdl::Font& font,
			const sdl::Renderer& rdr,
			std::string content
	):
		text {rdr.create_text(font, content, config.text_color)},
		box {config.box, rdr, text.size + sdl::Size {config.padding * 2}},
		padding {box.border + config.padding}
	{}

	void
	TextBox::render(const sdl::Renderer& rdr, sdl::Point pos) const
	{
		box.render(rdr, pos);
		rdr.put(text, pos + padding);
	}
}
