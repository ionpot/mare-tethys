#include "box.hpp"

#include <sdl/point.hpp>
#include <sdl/renderer.hpp>
#include <sdl/size.hpp>

namespace tethys::ui {
	Box::Box(
			const Box::Config& config,
			const sdl::Renderer& rdr,
			sdl::Size inner_size
	):
		content {sdl::Point {config.border_width} + config.padding},
		texture {rdr.create_target_texture(
			inner_size + sdl::Size {content * 2}
		)}
	{
		rdr.set_target(texture);
		rdr.set_color(config.background_color);
		rdr.clear();
		rdr.set_color(config.border_color);
		sdl::Point offset {0, 0};
		auto size = texture.size;
		for (auto i = config.border_width; i > 0; --i) {
			rdr.draw_rect({offset++, size});
			size -= 2;
		}
		rdr.reset_target();
	}

	void
	Box::render(const sdl::Renderer& rdr, sdl::Point pos) const
	{
		rdr.put(texture, pos);
	}
}
