#include "text_lines.hpp"

#include "font.hpp"
#include "point.hpp"
#include "renderer.hpp"
#include "size.hpp"
#include "text.hpp"

#include <util/int.hpp>
#include <util/rgba.hpp>

#include <string>
#include <utility>
#include <vector>

namespace tethys::sdl {
	namespace {
		std::vector<Text>
		s_lines(
				const Font& font,
				const Renderer& rdr,
				const std::vector<std::string>& lines,
				const util::RGBA& text_color)
		{
			std::vector<Text> vector;
			vector.reserve(lines.size());
			for (auto line : lines)
				vector.emplace_back(font, rdr, line, text_color);
			return vector;
		}
	}

	TextLines::TextLines(
			int lskip,
			std::vector<Text>&& lns
	):
		m_lines {std::move(lns)},
		m_line_skip {lskip},
		m_size {}
	{
		auto& [width, height] = m_size;
		for (const auto& line : m_lines) {
			if (auto w = line.width(); w > width)
				width = w;
		}
		if (auto sz = m_lines.size()) {
			auto h = m_lines.front().height();
			height = h + m_line_skip * TETHYS_INT(--sz);
		}
	}

	TextLines::TextLines(
			const Font& font,
			std::vector<Text>&& lines
	):
		TextLines {font.line_skip(), std::move(lines)}
	{}

	TextLines::TextLines(
			const Font& font,
			const Renderer& rdr,
			const std::vector<std::string>& lines,
			const util::RGBA& text_color
	):
		TextLines {font, s_lines(font, rdr, lines, text_color)}
	{}

	void
	TextLines::render(const Renderer& rdr, Point position) const
	{
		for (const auto& line : m_lines) {
			line.render(rdr, position);
			position.y += m_line_skip;
		}
	}

	Size
	TextLines::size() const
	{
		return m_size;
	}
}
