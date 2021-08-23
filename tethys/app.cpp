#include "app.hpp"

#include "screen.hpp"

#include <util/cfg_file.hpp>
#include <util/log.hpp>

#include <string>

namespace tethys {
	App::App(std::string title, util::Log& log):
		m_config {
			util::CfgFile {"game.cfg"},
			util::CfgFile {"ui.cfg"}
		},
		m_sdl {title, m_config.ui.window_size, log},
		m_screen {m_config.ui, m_sdl, log}
	{
		log.put("Ready");
	}

	void
	App::poll()
	{
		auto event = m_sdl.base.poll_event();
		if (event) {
			if (m_screen.handle(*event) == Screen::Status::quit)
				return;
		}
		else {
			m_screen.update();
			m_screen.render(m_sdl.renderer);
			m_sdl.base.delay(1000 / 30);
		}
		poll();
	}
}
