#pragma once

#include "exception.hpp"
#include "rgb.hpp"

#include <util/macros.hpp>

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>

namespace tethys::sdl {
	class Font {
	public:
		~Font();
		TETHYS_NO_COPY(Font)
		TETHYS_DECLARE_MOVE(Font)

		SDL_Surface& render_blended(std::string text, RGBA color) const;

	private:
		friend class Base;
		TTF_Font* m_font;
		Font(std::string file, int height);
	};
}
