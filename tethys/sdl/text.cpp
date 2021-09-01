#include "text.hpp"

#include "font.hpp"
#include "point.hpp"
#include "renderer.hpp"

#include <util/rgba.hpp>

#include <string>

namespace tethys::sdl {
	Text::Text(
			const Font& font,
			const Renderer& rdr,
			std::string content,
			const util::RGBA& color
	):
		m_texture {rdr.create_text(font, content, color)},
		m_size {m_texture.size.width, font.line_height()}
	{}

	void
	Text::render(const Renderer& rdr, Point pos) const
	{
		rdr.put(m_texture, pos);
	}

	Size
	Text::size() const
	{
		return m_size;
	}

	int
	Text::width() const
	{
		return m_size.width;
	}

	int
	Text::height() const
	{
		return m_size.height;
	}
}
