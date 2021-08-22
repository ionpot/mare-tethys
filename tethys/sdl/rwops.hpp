#pragma once

#include <util/macros.hpp>

#include <SDL.h>

#include <string>

namespace tethys::sdl {
	class RWops {
	public:
		static RWops read_binary_file(std::string filename);

		SDL_RWops* pointer;

		~RWops();
		TETHYS_NO_COPY(RWops)
		TETHYS_DECLARE_MOVE(RWops)

		bool is_null() const;

	private:
		RWops(SDL_RWops*);
	};
}
