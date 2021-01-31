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
	return 0;
}
