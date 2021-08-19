#pragma once

#include "box.hpp"
#include "font.hpp"
#include "point.hpp"
#include "renderer.hpp"
#include "size.hpp"
#include "text.hpp"

#include <util/rgb.hpp>

#include <string>

namespace tethys::sdl {
	struct TextBox {
		struct Config {
			Box::Config box;
			util::RGB text_color;
		};

		Text text;
		Box box;

		TextBox(
			const TextBox::Config&,
			const Renderer&,
			Text&& content);

		TextBox(
			const TextBox::Config&,
			const Font&,
			const Renderer&,
			std::string content);

		void render(const Renderer&, Point position) const;
	};
}
