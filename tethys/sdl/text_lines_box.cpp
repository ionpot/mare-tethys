#include "text_lines_box.hpp"

#include "box.hpp"
#include "font.hpp"
#include "point.hpp"
#include "renderer.hpp"
#include "text_box.hpp"
#include "text_lines.hpp"

#include <string>
#include <utility>
#include <vector>

namespace tethys::sdl {
	TextLinesBox::TextLinesBox(
			const Box::Config& config,
			const Renderer& rdr,
			TextLines&& content
	):
		m_lines {std::move(content)},
		m_box {config, rdr, m_lines.size}
	{}

	TextLinesBox::TextLinesBox(
			const TextBox::Config& config,
			const Font& font,
			const Renderer& rdr,
			const std::vector<std::string>& lines
	):
		TextLinesBox {
			config.box,
			rdr,
			TextLines {font, rdr, lines, config.text_color}
		}
	{}

	void
	TextLinesBox::render(const Renderer& rdr, Point position) const
	{
		m_box.render(rdr, position);
		m_lines.render(rdr, m_box.content(position));
	}
}
