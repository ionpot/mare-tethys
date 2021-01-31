#ifndef TETHYS_FILE_HPP
#define TETHYS_FILE_HPP

#include "exception.hpp"

#include <list>
#include <string>

namespace tethys::file {
	typedef std::list<std::string> LineList;

	class OpenFailed : public tethys::Exception {
	public:
		OpenFailed(const std::string filename);
	};

	LineList read_lines(const std::string filename);
}

#endif
