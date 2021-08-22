#include "base.hpp"

#include "exception.hpp"
#include "event.hpp"
#include "version.hpp"

#include <util/log.hpp>

#include <SDL.h>
#include <SDL_image.h>

#include <string>

namespace tethys::sdl {
	namespace {
		const struct {
			Uint32 init {SDL_INIT_VIDEO};
			int img_init {IMG_INIT_PNG};
		} s_flags;
	}

	Base::Base(util::Log& log):
		m_call_quit {true},
		m_event {},
		m_log {&log}
	{
		if (SDL_WasInit(s_flags.init))
			throw Exception {"Cannot re-initialize."};

		std::string error;
		{
			SDL_version sdl_ver;
			SDL_GetVersion(&sdl_ver);
			log.put("Initializing SDL " + version::to_string(sdl_ver) + "...");
			if (SDL_Init(s_flags.init)) {
				error = SDL_GetError();
				goto sdl_fail;
			}

			auto img_ver = version::to_string(*IMG_Linked_Version());
			log.put("Initializing SDL_image " + img_ver + "...");
			int img_ok {IMG_Init(s_flags.img_init) & s_flags.img_init};
			if (!img_ok) {
				error = IMG_GetError();
				goto img_fail;
			}
		}
		return;
img_fail:
		IMG_Quit();
sdl_fail:
		SDL_Quit();
		throw Exception {error};
	}

	Base::~Base()
	{
		if (m_call_quit) {
			m_log->put("Quitting SDL_image...");
			IMG_Quit();
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
