#include "box.hpp"

#include "point.hpp"
#include "renderer.hpp"
#include "size.hpp"

namespace tethys::sdl {
	Box::Box(
			const Box::Config& config,
			const Renderer& rdr,
			Size inner_size
	):
		m_content {Point {config.border_width} + config.padding},
		m_texture {rdr.create_target_texture(
			inner_size + Size {m_content * 2}
		)}
	{
		rdr.set_target(m_texture);
		rdr.set_color(config.background_color);
		rdr.clear();
		rdr.set_color(config.border_color);
		Point offset {0, 0};
		auto size = m_texture.size;
		for (auto i = config.border_width; i > 0; --i) {
			rdr.draw_rect({offset++, size});
			size -= 2;
		}
		rdr.reset_target();
	}

	Point
	Box::content(Point offset) const
	{
		return offset + m_content;
	}

	void
	Box::render(const Renderer& rdr, Point pos) const
	{
		rdr.put(m_texture, pos);
	}
}
