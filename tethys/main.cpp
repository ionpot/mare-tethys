#include "cfg_file.hpp"
#include "config.hpp"
#include "log.hpp"
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

	void poll(sdl::Context& sdl)
	{
		auto event = sdl.base.poll_event();
		if (event) {
			if (event->is_quit())
				return;
		}
		sdl.renderer.clear();
		sdl.renderer.present();
		sdl.base.delay(1000 / 30);
		poll(sdl);
	}

	void start(Log&& log)
	{
		auto title = get_title();
		log.put(title);
		try {
			log.put("Reading config...");
			Config config {
				CfgFile {"tethys.cfg"}
			};
			log.pair("Mountain gold", config.mountain.gold);
			sdl::Context sdl {title, {640, 480}, log};
			log.put("Polling events...");
			poll(sdl);
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
