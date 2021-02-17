#include "cfg_file.hpp"
#include "config.hpp"
#include "log.hpp"
#include "screen.hpp"
#include "sdl.hpp"

#include <tethys/version.hpp>
#include <iostream>
#include <string>

namespace tethys {
	std::string get_title()
	{
		return "Mare Tethys v"
			+ std::to_string(version.major)
			+ "."
			+ std::to_string(version.minor);
	}

	class Main {
	public:
		Main(const std::string title, Log& log):
			m_config {CfgFile {"tethys.cfg"}},
			m_sdl {sdl::Context {title, m_config.window_size, log}},
			m_screen {m_config, m_sdl.renderer, log}
		{}
		void poll()
		{
			auto event = m_sdl.base.poll_event();
			if (event) {
				if (event->is_quit())
					return;
				if (m_screen.handle(*event) == Screen::Status::quit)
					return;
			}
			else {
				m_screen.render(m_sdl.renderer);
				m_sdl.base.delay(1000 / 30);
			}
			poll();
		}
	private:
		Config m_config;
		sdl::Context m_sdl;
		Screen m_screen;
	};

	void start(Log&& log)
	{
		auto title = get_title();
		log.put(title);
		log.put("Begin");
		try {
			Main m {title, log};
			log.put("Polling events...");
			m.poll();
		}
		catch (const std::exception& err) {
			log.error(err.what());
		}
		log.put("End");
	}
}

int main(int, char **)
{
	try {
		tethys::start(tethys::Log {"tethys.log"});
	}
	catch (const std::exception& err) {
		std::cerr << err.what() << std::endl;
	}
	return 0;
}
