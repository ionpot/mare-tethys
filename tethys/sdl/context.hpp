#pragma once

#include "base.hpp"
#include "renderer.hpp"
#include "size.hpp"
#include "window.hpp"

#include <util/log.hpp>
#include <util/macros.hpp>

#include <string>

namespace tethys::sdl {
	struct Context { // member ordering important
		Base base;
		Window window;
		Renderer renderer;
		Context(std::string title, Size size, util::Log& log):
			base {log},
			window {title, size},
			renderer {window.create_renderer()}
		{}
		~Context() = default;
		TETHYS_NO_COPY(Context)
		TETHYS_DEFAULT_MOVE(Context)
	};
}
