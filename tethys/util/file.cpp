#include "file.hpp"

#include <fstream>
#include <list>
#include <string>

namespace tethys::util::file {
	std::ofstream
	open_w(std::string filename)
	{
		std::ofstream file {filename, std::ofstream::trunc};
		if (file.is_open())
			return file;
		throw OpenFailed {filename};
	}

	LineList
	read_lines(std::string filename)
	{
		std::ifstream file {filename};
		if (!file.is_open())
			throw OpenFailed {filename};
		LineList lines;
		std::string line;
		while (std::getline(file, line)) {
			if (line.empty())
				continue;
			if (line.back() == '\r') {
				line.pop_back();
				if (line.empty())
					continue;
			}
			lines.push_back(line);
		}
		return lines;
	}

	OpenFailed::OpenFailed(std::string filename):
		Exception {"Failed to open file: " + filename}
	{}
}
