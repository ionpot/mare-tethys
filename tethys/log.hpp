#ifndef TETHYS_LOG_HPP
#define TETHYS_LOG_HPP

#include "macros.hpp"

#include <fstream>
#include <string>

namespace tethys {
	struct Log {
		std::ofstream file;

		Log(const std::string filename);
		~Log() = default;
		TETHYS_NO_COPY(Log)
		TETHYS_DEFAULT_MOVE(Log)

		void error(const std::string);

		void pair(const std::string, double);
		void pair(const std::string, const std::string);

		void put(const std::string);

	private:
		void write_pair_key(const std::string key);
	};
}

#endif

