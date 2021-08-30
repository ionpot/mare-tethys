#pragma once

#include "surface.hpp"

#include <util/macros.hpp>
#include <util/rgba.hpp>

#include <SDL_ttf.h>

#include <string>

namespace tethys::sdl {
	class Font {
	public:
		~Font();
		TETHYS_NO_COPY(Font)
		TETHYS_DECLARE_MOVE(Font)

		int line_height() const;
		int line_skip() const;

		Surface render_blended(std::string text, const util::RGBA&) const;

	private:
		friend struct Ttf;
		TTF_Font* m_font;
		Font(std::string file, int height);
	};
}
