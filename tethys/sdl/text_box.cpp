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
			const Renderer& rdr,
			Texture&& content
	):
		text {std::move(content)},
		box {config.box, rdr, text.size}
	{}

	TextBox::TextBox(
			const TextBox::Config& config,
			const Font& font,
			const Renderer& rdr,
			std::string content
	):
		TextBox {config, rdr,
			rdr.create_text(font, content, config.text_color)
		}
	{}

	void
	TextBox::render(const Renderer& rdr, Point pos) const
	{
		box.render(rdr, pos);
		rdr.put(text, pos + box.content);
	}
}
