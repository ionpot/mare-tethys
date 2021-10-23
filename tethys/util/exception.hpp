#pragma once

#include <exception>
#include <string>

#define TETHYS_EXCEPTION_AS(name, category)\
	struct name : public tethys::util::Exception {\
		name(std::string text):\
			tethys::util::Exception {category, text}\
		{};\
	};

#define TETHYS_EXCEPTION(category)\
	TETHYS_EXCEPTION_AS(Exception, category)

namespace tethys::util {
	class Exception : public std::exception {
	public:
		std::string source;
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
		std::string final_text;
	};
}
