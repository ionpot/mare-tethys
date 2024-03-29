#include "app.hpp"

#include "screen.hpp"

#include <sdl/config.hpp>

#include <util/log.hpp>

#include <string>

namespace tethys {
	App::App(std::string title, const sdl::Config& config, util::Log& log):
		m_sdl {title, config, log},
		m_screen {config, m_sdl, log}
	{
		log.put("Ready");
	}

	void
	App::poll()
	{
		while (true) {
			auto event = m_sdl.poll_event();
			if (event) {
				auto status = m_screen.handle(*event, m_sdl);
				if (status == Screen::Status::quit)
					return;
			}
			else {
				m_screen.update(m_sdl);
				m_screen.render(m_sdl.renderer);
				m_sdl.base.delay(1000 / 30);
			}
		}
	}
}
