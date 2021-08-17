#pragma once

#include "point.hpp"
#include "renderer.hpp"
#include "size.hpp"
#include "texture.hpp"

#include <util/rgb.hpp>

namespace tethys::sdl {
	struct Box {
		struct Config {
			util::RGB background_color;
			util::RGB border_color;
			int border_width;
			Point padding;
		};

		const Point content;
		const TargetTexture texture;

		Box(const Config&, const Renderer&, Size inner_size);

		void render(const Renderer&, Point position) const;
	};
}
