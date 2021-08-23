#pragma once

#include "config.hpp"
#include "screen.hpp"

#include <sdl/context.hpp>

#include <util/log.hpp>

#include <string>

namespace tethys {
	class App {
	public:
		App(std::string window_title, util::Log&);
		void poll();
	private:
		const Config m_config;
		sdl::Context m_sdl;
		Screen m_screen;
	};
}
