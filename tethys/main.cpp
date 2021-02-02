#include "cfg_file.hpp"
#include "config.hpp"
#include "log.hpp"

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

	void start(Log&& log)
	{
		log.put(get_title());
		try {
			log.put("Reading config...");
			Config config {
				CfgFile {"tethys.cfg"}
			};
			log.pair("Mountain gold", config.mountain.gold);
		}
		catch (const std::exception& err) {
			log.error(err.what());
		}
		log.put("End");
	}
}

int main()
{
	try {
		tethys::start(tethys::Log {"tethys.log"});
	}
	catch (const std::exception& err) {
		std::cerr << err.what() << std::endl;
	}
	return 0;
}
