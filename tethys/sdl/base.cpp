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
		m_call_quit {true},
		m_event {},
		m_log {&log}
	{
		if (SDL_WasInit(init_flags))
			throw Exception {"Cannot re-initialize."};

		SDL_version sdl_ver;
		SDL_GetVersion(&sdl_ver);
		log.put("Initializing SDL " + version::to_string(sdl_ver) + "...");

		if (SDL_Init(init_flags)) {
			std::string error {SDL_GetError()};
			SDL_Quit();
			throw Exception {error};
		}
	}

	Base::~Base()
	{
		if (m_call_quit) {
			m_log->put("Quitting SDL...");
			SDL_Quit();
		}
	}

	Base::Base(Base&& from) noexcept:
		m_call_quit {true},
		m_event {from.m_event},
		m_log {from.m_log}
	{
		from.m_call_quit = false;
	}

	Base&
	Base::operator=(Base&& from) noexcept
	{
		m_call_quit = true;
		from.m_call_quit = false;
		m_event = from.m_event;
		m_log = from.m_log;
		return *this;
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
}
