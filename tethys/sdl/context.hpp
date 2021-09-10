#pragma once

#include "base.hpp"
#include "config.hpp"
#include "event.hpp"
#include "font.hpp"
#include "img.hpp"
#include "renderer.hpp"
#include "text_box.hpp"
#include "text_lines_box.hpp"
#include "texture.hpp"
#include "ttf.hpp"
#include "window.hpp"

#include <util/log.hpp>
#include <util/macros.hpp>

#include <string>
#include <vector>

namespace tethys::sdl {
	struct Context { // member ordering important
		Base base;
		Window window;
		Renderer renderer;
		Img img;
		Ttf ttf;
		Font font;
		TextBox::Config text_box_cfg;

		Context(std::string window_title, const Config&, util::Log&);
		~Context() = default;
		TETHYS_NO_COPY(Context)

		Texture load_png(std::string path) const;
		const Event* poll_event();

		TextLinesBox text_lines_box(const std::vector<std::string>& lines) const;
	};
}
