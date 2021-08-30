#include "text_lines.hpp"

#include "font.hpp"
#include "point.hpp"
#include "renderer.hpp"
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
		lines {std::move(lns)},
		line_skip {lskip},
		size {}
	{
		auto& [width, height] = size;
		for (const auto& line : lines) {
			if (auto w = line.size.width; w > width)
				width = w;
		}
		if (auto sz = lines.size()) {
			auto h = lines.front().size.height;
			height = h + line_skip * TETHYS_INT(--sz);
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
		for (const auto& line : lines) {
			line.render(rdr, position);
			position.y += line_skip;
		}
	}
}
