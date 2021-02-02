#include "log.hpp"

#include "file.hpp"

#include <fstream>
#include <string>

namespace tethys {
	Log::Log(const std::string filename):
		file {std::ofstream {filename, std::ofstream::trunc}}
	{
		if (!file.is_open())
			throw file::OpenFailed {filename};
		file.precision(2);
	}

	void
	Log::error(const std::string text)
	{
		put("[Error] " + text);
	}

	void
	Log::pair(const std::string key, double value)
	{
		write_pair_key(key);
		file << value << std::endl;
	}

	void
	Log::pair(const std::string key, const std::string value)
	{
		write_pair_key(key);
		file << value << std::endl;
	}

	void
	Log::put(const std::string line)
	{
		file << line << std::endl;
	}

	void
	Log::write_pair_key(const std::string key)
	{
		file << key << ": ";
	}
}
