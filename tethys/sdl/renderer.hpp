#pragma once

#include "font.hpp"
#include "hexagon.hpp"
#include "line.hpp"
#include "point.hpp"
#include "rgb.hpp"
#include "size.hpp"
#include "texture.hpp"

#include <util/macros.hpp>

#include <SDL.h>
#include <string>

namespace tethys::sdl {
	class Renderer {
	public:
		void clear() const;
		Texture create_hex(const Hexagon&, const RGB&) const;
		TargetTexture create_target_texture(Size) const;
		Texture create_texture_from_png(std::string filename) const;
		Texture create_text(const Font&, std::string text) const;
		Texture create_text(const Font&, std::string text, RGBA color) const;
		void draw_hex(const Hexagon&) const;
		void draw_line(Line) const;
		void present() const;
		void put(const Texture&, Point position) const;
		void reset_color() const;
		void reset_target() const;
		void set_color(RGBA) const;
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
