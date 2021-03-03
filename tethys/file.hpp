#ifndef TETHYS_FILE_HPP
#define TETHYS_FILE_HPP

#include "exception.hpp"

#include <list>
#include <string>

namespace tethys::file {
	typedef std::list<std::string> LineList;

	struct Exception : public tethys::Exception {
		Exception(std::string text):
			tethys::Exception {"File", text}
		{};
	};

	struct OpenFailed : public Exception {
		OpenFailed(std::string filename);
	};

	LineList read_lines(std::string filename);
}

#endif
