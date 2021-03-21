#pragma once

#include <exception>
#include <string>

namespace tethys::util {
	class Exception : public std::exception {
	public:
		const std::string source;
		std::string text;
		const char * what() const throw()
		{
			return final_text.c_str();
		}
	protected:
		Exception(std::string source, std::string text):
			source {source},
			text {text},
			final_text {"(" + source + ") " + text}
		{}
	private:
		const std::string final_text;
	};
}
