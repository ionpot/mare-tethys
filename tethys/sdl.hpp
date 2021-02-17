#ifndef TETHYS_SDL_HPP
#define TETHYS_SDL_HPP

#include "exception.hpp"
#include "hexagon.hpp"
#include "line.hpp"
#include "log.hpp"
#include "macros.hpp"
#include "point.hpp"
#include "rgb.hpp"
#include "size.hpp"

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
		bool is_keydown() const;
		bool is_quit() const;
		Point* read_mouse_motion();
	private:
		friend class Base;
		Event() = default;
		Event(SDL_Event);
		SDL_Event m_event;
		Point m_point;
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

	class Texture {
	public:
		Size size;
		~Texture();
		TETHYS_NO_COPY(Texture)
		TETHYS_DECLARE_MOVE(Texture)
	protected:
		friend class Renderer;
		SDL_Texture* m_texture;
		Texture(SDL_Renderer*, Size, Uint32 flags);
	};

	class TargetTexture : public Texture {
		friend class Renderer;
		TargetTexture(SDL_Renderer*, Size);
	};

	struct RGBA {
		RGB channels;
		int alpha;
		static const RGBA transparent;
		static RGBA opaque(RGB);
	};

	class Renderer {
	public:
		void clear() const;
		TargetTexture create_target_texture(Size) const;
		void draw_hex(Hexagon) const;
		void draw_line(Line) const;
		void present() const;
		void put(const Texture&, Point position) const;
		void reset_color() const;
		void reset_target() const;
		void set_color(RGBA) const;
		void set_target(const TargetTexture&) const;
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
		Renderer create_renderer() const;
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
		Context(const std::string title, Size size, Log&);
		~Context() = default;
		TETHYS_NO_COPY(Context)
		TETHYS_DEFAULT_MOVE(Context)
	};
}

#endif
