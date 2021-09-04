#include "app.hpp"

#include "screen.hpp"

#include <ui/config.hpp>

#include <util/log.hpp>

#include <string>

namespace tethys {
	App::App(std::string title, const ui::Config& ui, util::Log& log):
		m_sdl {title, ui.window_size, log},
		m_screen {ui, m_sdl, log}
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
