#pragma once

#include "box.hpp"
#include "font.hpp"
#include "point.hpp"
#include "renderer.hpp"
#include "text_box.hpp"
#include "text_lines.hpp"

#include <string>
#include <vector>

namespace tethys::sdl {
	struct TextLinesBox {
		TextLines lines;
		Box box;

		TextLinesBox(
			const Box::Config&,
			const Renderer&,
			TextLines&& content);

		TextLinesBox(
			const TextBox::Config&,
			const Font&,
			const Renderer&,
			const std::vector<std::string>& lines);

		void render(const Renderer&, Point position) const;
	};
}
