#include "rwops.hpp"

#include "exception.hpp"

#include <SDL.h>

#include <string>

namespace tethys::sdl {
	RWops
	RWops::read_binary_file(std::string filename)
	{
		return {SDL_RWFromFile(filename.c_str(), "rb")};
	}

	RWops::RWops(SDL_RWops* ptr):
		pointer {ptr}
	{
		if (is_null())
			throw Exception {};
	}

	RWops::~RWops()
	{
		if (pointer) {
			SDL_RWclose(pointer);
		}
	}

	RWops::RWops(RWops&& from) noexcept:
		pointer {from.pointer}
	{
		from.pointer = NULL;
	}

	RWops&
	RWops::operator=(RWops&& from) noexcept
	{
		pointer = from.pointer;
		from.pointer = NULL;
		return *this;
	}

	bool
	RWops::is_null() const
	{
		return pointer == NULL;
	}
}
