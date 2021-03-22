#include "config.hpp"
#include "screen.hpp"

#include <sdl/context.hpp>
#include <sdl/show_error.hpp>
#include <tethys/version.hpp>
#include <util/cfg_file.hpp>
#include <util/exception.hpp>
#include <util/log.hpp>

#include <iostream>
#include <string>

namespace tethys {
	std::string
	get_title()
	{
		return "Mare Tethys v" + version.to_string();
	}

	class Main {
	public:
		Main(std::string title, util::Log& log):
			m_config {util::CfgFile {"tethys.cfg"}},
			m_sdl {sdl::Context {title, m_config.window_size, log}},
			m_screen {m_config, m_sdl, log}
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
				m_screen.update();
				m_screen.render();
				m_sdl.base.delay(1000 / 30);
			}
			poll();
		}
	private:
		Config m_config;
		sdl::Context m_sdl;
		Screen m_screen;
	};

	void start(util::Log&& log)
	{
		auto title = get_title();
		log.put(title);
		log.put("Begin");
		try {
			Main m {title, log};
			log.put("Polling events...");
			m.poll();
		}
		catch (const util::Exception& err) {
			sdl::show_error(err.source + " Error", err.text);
			log.error(err.what());
		}
		catch (const std::exception& err) {
			sdl::show_error("System Error", err.what());
			log.error(err.what());
		}
		log.put("End");
	}
}

int main(int, char **)
{
	try {
		tethys::start(tethys::util::Log {"tethys.log"});
	}
	catch (const std::exception& err) {
		std::cerr << err.what() << std::endl;
	}
	return 0;
}
