#ifndef TETHYS_SDL_HPP
#define TETHYS_SDL_HPP

#include "exception.hpp"
#include "log.hpp"
#include "macros.hpp"

#include <SDL.h>
#include <string>

namespace tethys::sdl {
	struct Exception : public tethys::Exception {
		Exception(const std::string text):
			tethys::Exception {"SDL", text}
		{}
	};

	class Event {
	public:
		bool is_quit() const;
	private:
		friend class Base;
		Event() = default;
		Event(SDL_Event);
		SDL_Event m_event;
	};

	class Base {
	public:
		void delay(Uint32 milliseconds) const;
		Event* poll_event();
	private:
		friend struct Context;
		bool m_call_quit;
		Event m_event;
		std::reference_wrapper<Log> m_log;
		Base(Log&);
		~Base();
		TETHYS_NO_COPY(Base)
		TETHYS_DECLARE_MOVE(Base)
	};


	class Renderer {
	public:
		void clear();
		void present();
	private:
		friend struct Context;
		friend class Window;
		SDL_Renderer* m_renderer;
		Renderer(SDL_Window*);
		~Renderer();
		TETHYS_NO_COPY(Renderer)
		TETHYS_DECLARE_MOVE(Renderer)
	};

	class Window {
	public:
		struct Size {
			int width;
			int height;
		};
		Renderer create_renderer();
	private:
		friend struct Context;
		SDL_Window* m_window;
		Window(const std::string title, Size window_size);
		~Window();
		TETHYS_NO_COPY(Window)
		TETHYS_DECLARE_MOVE(Window)
	};

	struct Context { // member ordering important
		Base base;
		Window window;
		Renderer renderer;
		Context(const std::string title, Window::Size size, Log&);
		~Context() = default;
		TETHYS_NO_COPY(Context)
		TETHYS_DEFAULT_MOVE(Context)
	};
}

#endif
