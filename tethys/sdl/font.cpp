#include "font.hpp"

#include "color.hpp"
#include "size.hpp"
#include "surface.hpp"
#include "ttf_exception.hpp"

#include <util/int.hpp>
#include <util/rgba.hpp>

#include <SDL_ttf.h>

#include <list>
#include <string>

namespace tethys::sdl {
	Font::Font(std::string file, int height):
		m_font {TTF_OpenFont(file.c_str(), height)}
	{
		if (m_font == NULL)
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
	Font::calculate_height(int lines) const
	{
		return (lines > 0)
			? line_height() + line_skip() * --lines
			: 0;
	}

	Size
	Font::calculate_size(const std::string& text) const
	{
		Size size;
		if (TTF_SizeUTF8(m_font, text.c_str(), &size.width, &size.height))
			throw TtfException {};
		return size;
	}

	Size
	Font::calculate_size(const std::list<std::string>& lines) const
	{
		auto count = TETHYS_INT(lines.size());
		int width {0};
		for (const auto& line : lines) {
			auto size = calculate_size(line);
			if (size.width > width)
				width = size.width;
		}
		return {width, calculate_height(count)};
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

	int
	Font::y_of_line(int nth_line) const
	{
		return line_skip() * nth_line;
	}
}
