#include "text_box.hpp"

#include <sdl/font.hpp>
#include <sdl/point.hpp>
#include <sdl/renderer.hpp>
#include <sdl/texture.hpp>

#include <string>
#include <utility>

namespace tethys::sdl {
	TextBox::TextBox(
			const TextBox::Config& config,
			const Font& font,
			const Renderer& rdr,
			std::string content
	):
		text {rdr.create_text(font, content, config.text_color)},
		size {text.size.width, font.line_height() + 1},
		box {config.box, rdr, size}
	{}

	void
	TextBox::render(const Renderer& rdr, Point pos) const
	{
		box.render(rdr, pos);
		rdr.put(text, pos + box.content);
	}
}
