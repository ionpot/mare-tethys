#include "ttf.hpp"

#include "font.hpp"
#include "ttf_exception.hpp"
#include "version.hpp"

#include <util/log.hpp>

#include <SDL_ttf.h>

#include <string>

namespace tethys::sdl {
	bool
	Ttf::was_init()
	{
		return TTF_WasInit();
	}

	Ttf::Ttf(util::Log& log)
	{
		if (was_init())
			throw TtfException {"Already initialised."};

		auto ver = version::to_string(*TTF_Linked_Version());
		log.put("Initializing SDL_ttf " + ver);

		if (TTF_Init() == -1)
			throw TtfException {};
	}

	Ttf::~Ttf()
	{
		if (was_init())
			TTF_Quit();
	}

	Font
	Ttf::load_font(std::string file, int height) const
	{
		return {file, height};
	}
}
