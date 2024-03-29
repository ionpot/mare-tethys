#pragma once

#include "font.hpp"
#include "hexagon.hpp"
#include "line.hpp"
#include "point.hpp"
#include "rect.hpp"
#include "size.hpp"
#include "surface.hpp"
#include "texture.hpp"

#include <util/rgba.hpp>
#include <util/macros.hpp>

#include <SDL.h>
#include <string>

namespace tethys::sdl {
	class Renderer {
	public:
		void clear() const;
		Texture create_hex(const Hexagon&, const util::RGBA&) const;
		TargetTexture create_target_texture(Size) const;
		Texture create_text(const Font&, std::string text) const;
		Texture create_text(const Font&, std::string text, const util::RGBA&) const;
		Texture create_texture(const Surface& surface) const;
		void draw_hex(const Hexagon&) const;
		void draw_line(Line) const;
		void draw_rect(const Rect&) const;
		void present() const;
		void put(const Texture&, Point position) const;
		void reset_color() const;
		void reset_target() const;
		void set_color(const util::RGBA&) const;
		void set_target(const TargetTexture&) const;
	private:
		friend struct Context;
		friend class Window;
		SDL_Renderer* m_renderer;
		Renderer(SDL_Window*);
		~Renderer();
		TETHYS_NO_COPY(Renderer)
		TETHYS_DECLARE_MOVE(Renderer)
	};
}
