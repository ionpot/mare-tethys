#include "img.hpp"

#include "img_exception.hpp"
#include "rwops.hpp"
#include "surface.hpp"
#include "version.hpp"

#include <util/log.hpp>

#include <SDL_image.h>

#include <string>

namespace tethys::sdl {
	int
	Img::init_flags {IMG_INIT_PNG};

	bool
	Img::was_init {false};

	Img::Img(util::Log& log)
	{
		if (was_init)
			throw ImgException {"Already initialised."};

		auto ver = version::to_string(*IMG_Linked_Version());
		log.put("Initializing SDL_image " + ver);

		auto flags = IMG_Init(init_flags) & init_flags;
		if (flags != init_flags) {
			ImgException ex;
			IMG_Quit();
			throw ex;
		}

		was_init = true;
	}

	Img::~Img()
	{
		if (was_init) {
			IMG_Quit();
			was_init = false;
		}
	}

	Surface
	Img::load_png(const RWops& rwops) const
	{
		Surface surface {IMG_LoadPNG_RW(rwops.pointer)};
		if (surface.is_null())
			throw ImgException {};
		return surface;
	}
}
