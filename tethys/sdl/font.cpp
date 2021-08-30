#include "font.hpp"

#include "color.hpp"
#include "surface.hpp"
#include "ttf_exception.hpp"

#include <util/rgba.hpp>

#include <SDL_ttf.h>

#include <string>

namespace tethys::sdl {
	Font::Font(std::string file, int height):
		m_font {TTF_OpenFont(file.c_str(), height)}
	{
		if (!m_font)
			throw TtfException {};
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

	int
	Font::line_height() const
	{
		return TTF_FontHeight(m_font);
	}

	int
	Font::line_skip() const
	{
		return TTF_FontLineSkip(m_font);
	}

	Surface
	Font::render_blended(std::string text, const util::RGBA& color) const
	{
		Surface surface {
			TTF_RenderUTF8_Blended(m_font, text.c_str(), color_rgba(color))
		};
		if (!surface.pointer)
			throw TtfException {};
		return surface;
	}
}
