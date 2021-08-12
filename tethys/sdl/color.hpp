#pragma once

#include <util/rgba.hpp>

#include <SDL.h>

namespace tethys::sdl {
	SDL_Color
	color_rgba(const util::RGBA& color)
	{
		return {
			color.channels.red,
			color.channels.green,
			color.channels.blue,
			color.alpha
		};
	}
}
