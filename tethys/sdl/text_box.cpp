#include "text_box.hpp"

#include "font.hpp"
#include "point.hpp"
#include "renderer.hpp"
#include "text.hpp"

#include <string>
#include <utility>

namespace tethys::sdl {
	TextBox::TextBox(
			const TextBox::Config& config,
			const Renderer& rdr,
			Text&& content
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
		TextBox {config, rdr, Text {font, rdr, content, config.text_color}}
	{}

	void
	TextBox::render(const Renderer& rdr, Point pos) const
	{
		box.render(rdr, pos);
		text.render(rdr, pos + box.content);
	}
}
