#include "context.hpp"

#include "event.hpp"
#include "size.hpp"
#include "texture.hpp"

#include <util/log.hpp>

#include <string>

namespace tethys::sdl {
	Context::Context(std::string title, Size window_size, util::Log& log):
		base {log},
		window {title, window_size},
		renderer {window.create_renderer()},
		img {log},
		ttf {log}
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
}
