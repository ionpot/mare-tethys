#pragma once

#include <SDL.h>

#include <string>

namespace tethys::sdl::version {
	std::string
	to_string(const SDL_version& v)
	{
		return std::to_string(v.major)
			+ "." + std::to_string(v.minor)
			+ "." + std::to_string(v.patch);
	}
}
