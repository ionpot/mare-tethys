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
	struct TextLines {
		std::vector<Text> lines;
		int line_skip;
		Size size;

		TextLines(int line_skip, std::vector<Text>&& lines);
		TextLines(const Font&, std::vector<Text>&& lines);
		TextLines(
			const Font&,
			const Renderer&,
			const std::vector<std::string>& lines,
			const util::RGBA& text_color);

		void render(const Renderer&, Point position) const;
	};
}
