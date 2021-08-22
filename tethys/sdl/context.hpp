#pragma once

#include "base.hpp"
#include "img.hpp"
#include "renderer.hpp"
#include "size.hpp"
#include "texture.hpp"
#include "ttf.hpp"
#include "window.hpp"

#include <util/log.hpp>
#include <util/macros.hpp>

#include <string>

namespace tethys::sdl {
	struct Context { // member ordering important
		Base base;
		Window window;
		Renderer renderer;
		Img img;
		Ttf ttf;

		Context(std::string window_title, Size window_size, util::Log&);
		~Context() = default;
		TETHYS_NO_COPY(Context)

		Texture load_png(std::string path) const;
	};
}
