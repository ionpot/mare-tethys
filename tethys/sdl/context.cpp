#include "context.hpp"

#include "config.hpp"
#include "event.hpp"
#include "text_lines_box.hpp"
#include "texture.hpp"

#include <util/log.hpp>

#include <string>
#include <vector>

namespace tethys::sdl {
	Context::Context(std::string title, const Config& config, util::Log& log):
		base {log},
		window {title, config.window_size},
		renderer {window.create_renderer()},
		img {log},
		ttf {log},
		font {ttf.load_font(config.font)},
		text_box_cfg {config.text_box}
	{}

	Texture
	Context::load_png(std::string path) const
	{
		auto rwops = base.read_binary_file(path);
		auto surface = img.load_png(rwops);
		return renderer.create_texture(surface);
	}

	const Event*
	Context::poll_event()
	{
		auto* event = base.poll_event();
		if (event)
			window.handle(*event);
		return event;
	}

	TextLinesBox
	Context::text_lines_box(const std::vector<std::string>& lines) const
	{
		return {text_box_cfg, font, renderer, lines};
	}
}
