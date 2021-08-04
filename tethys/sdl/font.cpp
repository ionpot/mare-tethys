#include "font.hpp"

#include "exception.hpp"
#include "rgb.hpp"

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>

namespace tethys::sdl {
	Font::Font(std::string file, int height):
		m_font {TTF_OpenFont(file.c_str(), height)}
	{
		if (!m_font)
			throw Exception {TTF_GetError()};
	}

	Font::~Font()
	{
		if (m_font) {
			TTF_CloseFont(m_font);
			m_font = NULL;
		}
	}

	Font::Font(Font&& from) noexcept:
		m_font {from.m_font}
	{
		from.m_font = NULL;
	}

	Font&
	Font::operator=(Font&& from) noexcept
	{
		m_font = from.m_font;
		from.m_font = NULL;
		return *this;
	}

	SDL_Surface&
	Font::render_blended(std::string text, RGBA color) const
	{
		SDL_Surface* surface {
			TTF_RenderUTF8_Blended(m_font, text.c_str(), color.to_sdl())
		};
		if (!surface)
			throw Exception {TTF_GetError()};
		return *surface;
	}
}
