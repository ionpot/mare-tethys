#ifndef TETHYS_EXCEPTION_HPP
#define TETHYS_EXCEPTION_HPP

#include <exception>
#include <string>

namespace tethys {
	class Exception : public std::exception {
	public:
		const std::string source;
		std::string text;
		const char * what() const throw()
		{
			return final_text.c_str();
		}
	protected:
		Exception(const std::string source, const std::string text):
			source {source},
			text {text},
			final_text {"(" + source + ") " + text}
		{}
	private:
		const std::string final_text;
	};
}

#endif
