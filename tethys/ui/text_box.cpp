#include "text_box.hpp"

#include <sdl/font.hpp>
#include <sdl/point.hpp>
#include <sdl/renderer.hpp>
#include <sdl/texture.hpp>

#include <string>
#include <utility>

namespace tethys::ui {
	TextBox::TextBox(
			const TextBox::Config& config,
			const sdl::Renderer& rdr,
			sdl::Texture&& content
	):
		text {std::move(content)},
		box {config.box, rdr, text.size}
	{}

	TextBox::TextBox(
			const TextBox::Config& config,
			const sdl::Font& font,
			const sdl::Renderer& rdr,
			std::string content
	):
		TextBox {config, rdr,
			rdr.create_text(font, content, config.text_color)
		}
	{}

	void
	TextBox::render(const sdl::Renderer& rdr, sdl::Point pos) const
	{
		box.render(rdr, pos);
		rdr.put(text, pos + box.content);
	}
}
