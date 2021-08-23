#include "base.hpp"

#include "exception.hpp"
#include "event.hpp"
#include "version.hpp"

#include <util/log.hpp>

#include <SDL.h>

#include <string>

namespace tethys::sdl {
	Uint32
	Base::init_flags {SDL_INIT_VIDEO};

	Base::Base(util::Log& log):
		m_event {}
	{
		if (SDL_WasInit(init_flags))
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
		if (SDL_WasInit(init_flags))
			SDL_Quit();
	}

	void
	Base::delay(Uint32 milliseconds) const
	{
		SDL_Delay(milliseconds);
	}

	Event*
	Base::poll_event()
	{
		SDL_Event event;
		if (SDL_PollEvent(&event)) {
			m_event = Event {event};
			return &m_event;
		}
		return nullptr;
	}

	RWops
	Base::read_binary_file(std::string path) const
	{
		return {SDL_RWFromFile(path.c_str(), "rb")};
	}
}
