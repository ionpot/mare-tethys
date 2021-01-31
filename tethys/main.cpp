#include "file.hpp"

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
		auto lines = tethys::file::read_lines("tethys.cfg");
		std::cout << "Config line count: " << lines.size() << std::endl;
	} catch (const tethys::file::OpenFailed& err) {
		std::cout << err.what() << std::endl;
	}
	return 0;
}
