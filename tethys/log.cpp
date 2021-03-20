#include "log.hpp"

#include <util/file.hpp>

#include <fstream>
#include <string>

namespace tethys {
	Log::Log(std::string filename):
		file {std::ofstream {filename, std::ofstream::trunc}}
	{
		if (!file.is_open())
			throw util::file::OpenFailed {filename};
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
