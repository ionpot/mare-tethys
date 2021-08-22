#include "context.hpp"

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
		auto surface = img.load_png(path);
		return renderer.create_texture(surface);
	}
}
