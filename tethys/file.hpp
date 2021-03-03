#ifndef TETHYS_FILE_HPP
#define TETHYS_FILE_HPP

#include "exception.hpp"

#include <list>
#include <string>

namespace tethys::file {
	typedef std::list<std::string> LineList;

	struct FileException : public Exception {
		FileException(std::string text):
			Exception {"File", text}
		{};
	};

	struct OpenFailed : public FileException {
		OpenFailed(std::string filename);
	};

	LineList read_lines(std::string filename);
}

#endif
