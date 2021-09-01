#pragma once

#include "font.hpp"
#include "point.hpp"
#include "renderer.hpp"
#include "size.hpp"
#include "texture.hpp"

#include <util/rgba.hpp>

#include <string>

namespace tethys::sdl {
	class Text {
	public:
		Text(
			const Font&,
			const Renderer&,
			std::string content,
			const util::RGBA& text_color);

		void render(const Renderer&, Point position) const;

		Size size() const;
		int width() const;
		int height() const;

	private:
		Texture m_texture;
		Size m_size;
	};
}
