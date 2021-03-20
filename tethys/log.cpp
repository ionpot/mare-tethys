#include "log.hpp"

#include <util/file.hpp>

#include <fstream>
#include <string>

namespace tethys {
	Log::Log(std::string filename):
		file {util::file::open_w(filename)}
	{
		file.precision(2);
	}

	void
	Log::error(std::string text)
	{
		put("[Error] " + text);
	}

	void
	Log::put(std::string line)
	{
		file << line << std::endl;
	}

	void
	Log::write_pair_key(std::string key)
	{
		file << key << ": ";
	}
}
