#pragma once

#include <sdl/point.hpp>
#include <sdl/renderer.hpp>
#include <sdl/size.hpp>
#include <sdl/texture.hpp>

#include <util/rgb.hpp>

namespace tethys::ui {
	struct Box {
		struct Config {
			util::RGB background_color;
			util::RGB border_color;
			int border_width;
			sdl::Point padding;
		};

		const sdl::Point content;
		const sdl::TargetTexture texture;

		Box(const Config&, const sdl::Renderer&, sdl::Size inner_size);

		void render(const sdl::Renderer&, sdl::Point position) const;
	};
}
