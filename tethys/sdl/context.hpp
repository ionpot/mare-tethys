#pragma once

#include "base.hpp"
#include "renderer.hpp"
#include "size.hpp"
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
		Ttf ttf;
		Context(std::string title, Size size, util::Log& log):
			base {log},
			window {title, size},
			renderer {window.create_renderer()},
			ttf {log}
		{}
		~Context() = default;
		TETHYS_NO_COPY(Context)
	};
}
