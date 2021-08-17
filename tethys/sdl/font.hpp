#pragma once

#include "size.hpp"

#include <util/macros.hpp>
#include <util/rgba.hpp>

#include <SDL.h>
#include <SDL_ttf.h>

#include <list>
#include <string>

namespace tethys::sdl {
	class Font {
	public:
		~Font();
		TETHYS_NO_COPY(Font)
		TETHYS_DECLARE_MOVE(Font)

		int calculate_height(int lines) const;
		Size calculate_size(const std::string& text) const;
		Size calculate_size(const std::list<std::string>& lines) const;
		int line_height() const;
		int line_height(int nth_line) const;
		int line_skip() const;
		SDL_Surface& render_blended(std::string text, const util::RGBA&) const;
		int y_of_line(int nth_line) const;

	private:
		friend class Base;
		TTF_Font* m_font;
		Font(std::string file, int height);
	};
}
