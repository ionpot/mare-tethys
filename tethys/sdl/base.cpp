#include "base.hpp"

#include "exception.hpp"
#include "event.hpp"

#include <util/log.hpp>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <string>

namespace tethys::sdl {
	namespace {
		const struct {
			Uint32 init {SDL_INIT_VIDEO};
			int img_init {IMG_INIT_PNG};
		} s_flags;

		std::string
		s_version_str(const SDL_version& v)
		{
			return std::to_string(v.major)
				+ "." + std::to_string(v.minor)
				+ "." + std::to_string(v.patch);
		}
	}

	Base::Base(util::Log& log):
		m_call_quit {true},
		m_event {},
		m_log {&log}
	{
		if (SDL_WasInit(s_flags.init))
			throw Exception {"Cannot re-initialize."};

		SDL_version sdl_ver;
		SDL_GetVersion(&sdl_ver);
		log.put("Initializing SDL " + s_version_str(sdl_ver) + "...");
		if (SDL_Init(s_flags.init)) {
			std::string text {SDL_GetError()};
			SDL_Quit();
			throw Exception {text};
		}

		auto img_ver = s_version_str(*IMG_Linked_Version());
		log.put("Initializing SDL_image " + img_ver + "...");
		int img_ok {IMG_Init(s_flags.img_init) & s_flags.img_init};
		if (!img_ok) {
			std::string text {IMG_GetError()};
			IMG_Quit();
			throw Exception {text};
		}

		auto ttf_ver = s_version_str(*TTF_Linked_Version());
		log.put("Initializing SDL_ttf " + ttf_ver + "...");
		if (TTF_Init() == -1) {
			std::string text {TTF_GetError()};
			TTF_Quit();
			throw Exception {text};
		}
	}

	Base::~Base()
	{
		if (m_call_quit) {
			m_log->put("Quitting SDL_ttf...");
			TTF_Quit();
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

	Font
	Base::create_font(std::string file, int height) const
	{
		return {file, height};
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
