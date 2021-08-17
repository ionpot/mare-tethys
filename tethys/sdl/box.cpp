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
		content {Point {config.border_width} + config.padding},
		texture {rdr.create_target_texture(
			inner_size + Size {content * 2}
		)}
	{
		rdr.set_target(texture);
		rdr.set_color(config.background_color);
		rdr.clear();
		rdr.set_color(config.border_color);
		Point offset {0, 0};
		auto size = texture.size;
		for (auto i = config.border_width; i > 0; --i) {
			rdr.draw_rect({offset++, size});
			size -= 2;
		}
		rdr.reset_target();
	}

	void
	Box::render(const Renderer& rdr, Point pos) const
	{
		rdr.put(texture, pos);
	}
}
