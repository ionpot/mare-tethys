#pragma once

#include <util/exception.hpp>

#include <SDL_image.h>

#include <string>

namespace tethys::sdl {
	struct ImgException : public util::Exception {
		ImgException(std::string text):
			util::Exception {"IMG", text}
		{}
		ImgException():
			ImgException {IMG_GetError()}
		{}
	};
}
