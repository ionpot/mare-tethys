#include "base.hpp"

#include "exception.hpp"
#include "event.hpp"
#include "version.hpp"

#include <util/log.hpp>

#include <SDL.h>

#include <optional>
#include <string>

namespace tethys::sdl {
	Uint32
	Base::init_flags {SDL_INIT_VIDEO};

	bool
	Base::was_init()
	{
		auto on = SDL_WasInit(init_flags) & init_flags;
		return on == init_flags;
	}

	Base::Base(util::Log& log)
	{
		if (was_init())
			throw Exception {"Cannot re-initialize."};

		SDL_version ver;
		SDL_GetVersion(&ver);
		log.put("Initializing SDL " + version::to_string(ver));

		if (SDL_Init(init_flags)) {
			Exception ex;
			SDL_Quit();
			throw ex;
		}
	}

	Base::~Base()
	{
		if (was_init())
			SDL_Quit();
	}

	void
	Base::delay(Uint32 milliseconds) const
	{
		SDL_Delay(milliseconds);
	}

	std::optional<Event>
	Base::poll_event() const
	{
		SDL_Event event;
		if (SDL_PollEvent(&event)) {
			return {Event {event}};
		}
		return {};
	}

	RWops
	Base::read_binary_file(std::string path) const
	{
		return {SDL_RWFromFile(path.c_str(), "rb")};
	}
}
