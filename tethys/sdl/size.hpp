#ifndef TETHYS_SDL_SIZE_HPP
#define TETHYS_SDL_SIZE_HPP

#include <string>

namespace tethys::sdl {
	struct Size {
		int width = 0;
		int height = 0;
		Size operator+(const Size& size) const
		{
			return {width + size.width, height + size.height};
		}
		Size operator-(const Size& size) const
		{
			return {width - size.width, height - size.height};
		}
		std::string to_str() const
		{
			return std::to_string(width)
				+ "x"
				+ std::to_string(height);
		}
	};
}

#endif
