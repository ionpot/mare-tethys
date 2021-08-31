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
		m_text {std::move(content)},
		m_box {config.box, rdr, m_text.size}
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
		m_box.render(rdr, pos);
		m_text.render(rdr, m_box.content(pos));
	}
}
