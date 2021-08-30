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
		texture {rdr.create_text(font, content, color)},
		size {texture.size.width, font.line_height()}
	{}

	void
	Text::render(const Renderer& rdr, Point pos) const
	{
		rdr.put(texture, pos);
	}
}
