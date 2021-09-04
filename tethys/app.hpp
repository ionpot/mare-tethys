#pragma once

#include "screen.hpp"

#include <sdl/context.hpp>

#include <ui/config.hpp>

#include <util/log.hpp>

#include <string>

namespace tethys {
	class App {
	public:
		App(std::string window_title, const ui::Config&, util::Log&);
		void poll();
	private:
		sdl::Context m_sdl;
		Screen m_screen;
	};
}
