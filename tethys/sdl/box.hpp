#pragma once

#include "point.hpp"
#include "renderer.hpp"
#include "size.hpp"
#include "texture.hpp"

#include <util/rgb.hpp>

namespace tethys::sdl {
	class Box {
	public:
		struct Config {
			util::RGB background_color;
			util::RGB border_color;
			int border_width;
			Point padding;
		};

		Box(const Config&, const Renderer&, Size inner_size);

		Point content(Point offset) const;

		void render(const Renderer&, Point position) const;

	private:
		Point m_content;
		TargetTexture m_texture;
	};
}
