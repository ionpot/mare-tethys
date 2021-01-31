#ifndef TETHYS_EXCEPTION_HPP
#define TETHYS_EXCEPTION_HPP

#include <exception>
#include <string>

namespace tethys {
	class Exception : public std::exception {
	public:
		const char * what() const throw()
		{
			return m_text.c_str();
		}
	protected:
		std::string m_text;
		Exception(const std::string text):
			m_text {text}
		{}
	};
}

#endif
