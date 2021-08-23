#include "app.hpp"

#include <sdl/show_error.hpp>

#include <tethys/version.hpp>

#include <util/exception.hpp>
#include <util/log.hpp>

#include <iostream>
#include <string>

using namespace tethys;

namespace {
	std::string
	get_title()
	{
		return "Mare Tethys v" + version.to_string();
	}

	void
	start(util::Log&& log)
	{
		auto title = get_title();
		log.put(title);
		log.put("Begin");
		try {
			App app {title, log};
			log.put("Polling events...");
			app.poll();
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
		start(util::Log {"tethys.log"});
	}
	catch (const std::exception& err) {
		std::cerr << err.what() << std::endl;
	}
	return 0;
}
