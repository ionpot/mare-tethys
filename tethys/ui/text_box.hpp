#pragma once

#include "box.hpp"

#include <sdl/font.hpp>
#include <sdl/point.hpp>
#include <sdl/renderer.hpp>

#include <util/rgb.hpp>

#include <list>
#include <string>

namespace tethys::ui {
	struct TextBox {
		struct Config {
			Box::Config box;
			util::RGB text_color;
		};

		const sdl::Texture text;
		const Box box;

		TextBox(
			const TextBox::Config&,
			const sdl::Renderer&,
			sdl::Texture&& content);

		TextBox(
			const TextBox::Config&,
			const sdl::Font&,
			const sdl::Renderer&,
			std::string content);

		void render(const sdl::Renderer&, sdl::Point position) const;
	};
}
