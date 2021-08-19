#pragma once

#include "box.hpp"
#include "font.hpp"
#include "point.hpp"
#include "renderer.hpp"
#include "size.hpp"
#include "texture.hpp"

#include <util/rgb.hpp>

#include <string>

namespace tethys::sdl {
	struct TextBox {
		struct Config {
			Box::Config box;
			util::RGB text_color;
		};

		const Texture text;
		const Size size;
		const Box box;

		TextBox(
			const TextBox::Config&,
			const Font&,
			const Renderer&,
			std::string content);

		void render(const Renderer&, Point position) const;
	};
}
