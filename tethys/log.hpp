#ifndef TETHYS_LOG_HPP
#define TETHYS_LOG_HPP

#include "macros.hpp"
#include "point.hpp"
#include "size.hpp"

#include <fstream>
#include <string>
#include <utility>

namespace tethys {
	struct Log {
		std::ofstream file;

		Log(const std::string filename);
		~Log() = default;
		TETHYS_NO_COPY(Log)
		TETHYS_DEFAULT_MOVE(Log)

		void error(const std::string);

		template<class T>
		void pair(const std::string key, T value)
		{
			write_pair_key(key);
			file << std::forward(value) << std::endl;
		}

		template<>
		void pair(const std::string key, Size size)
		{
			write_pair_key(key);
			file << size.width << "x" << size.height << std::endl;
		}

		template<>
		void pair(const std::string key, Point p)
		{
			write_pair_key(key);
			file << p.x << " " << p.y << std::endl;
		}

		void put(const std::string);

	private:
		void write_pair_key(const std::string key);
	};
}

#endif
