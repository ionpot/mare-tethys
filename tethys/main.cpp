#include "config.hpp"
#include "exception.hpp"

#include <tethys/version.hpp>
#include <iostream>

int main()
{
	std::cout
		<< "Version: "
		<< tethys::version.major
		<< "."
		<< tethys::version.minor
		<< std::endl;
	try {
		tethys::Config config {
			tethys::CfgFile {"tethys.cfg"}
		};
		auto city = config.city;
		std::cout << "city.gold = " << city.gold << std::endl;
		std::cout << "city.industry = " << city.industry << std::endl;
		std::cout << "city.manpower = " << city.manpower << std::endl;
		std::cout << "gold per trade = "
			<< config.gold_per_trade
			<< std::endl;
	}
	catch (const tethys::Exception& err) {
		std::cerr << err.what() << std::endl;
	}
	return 0;
}
