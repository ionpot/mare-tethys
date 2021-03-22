#pragma once

#include <SDL.h>

namespace tethys::sdl {
	struct RGB {
		Uint8 red;
		Uint8 green;
		Uint8 blue;
	};
	struct RGBA {
		RGB channels;
		Uint8 alpha;
	};
	namespace rgb {
		const RGB black {0, 0, 0};
		const RGB dark_blue {50, 50, 150};
		const RGB red {255, 0, 0};
	}
	namespace rgba {
		const RGBA transparent {rgb::black, SDL_ALPHA_TRANSPARENT};
		inline RGBA opaque(RGB channels)
		{
			return {channels, SDL_ALPHA_OPAQUE};
		}
	}
}
