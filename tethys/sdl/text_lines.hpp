#pragma once

#include "font.hpp"
#include "point.hpp"
#include "renderer.hpp"
#include "size.hpp"
#include "text.hpp"

#include <util/rgba.hpp>

#include <string>
#include <vector>

namespace tethys::sdl {
	class TextLines {
	public:
		TextLines(int line_skip, std::vector<Text>&& lines);
		TextLines(const Font&, std::vector<Text>&& lines);
		TextLines(
			const Font&,
			const Renderer&,
			const std::vector<std::string>& lines,
			const util::RGBA& text_color);

		void render(const Renderer&, Point position) const;

		Size size() const;

	private:
		std::vector<Text> m_lines;
		int m_line_skip;
		Size m_size;
	};
}
