#pragma once

#include "key.hpp"
#include "point.hpp"

#include <SDL.h>
#include <variant>

namespace tethys::sdl {
	struct KeyEvent {
		bool pressed {false};
		Key key {Key::other};
	private:
		friend class Event;
		KeyEvent(bool, SDL_Keycode);
	};

	class WindowEvent {
	public:
		bool got_focus() const;
		bool lost_focus() const;
	private:
		friend class Event;
		Uint8 m_id;
		WindowEvent(Uint8);
	};

	class Event {
	public:
		bool is_quit() const;
		const Point* read_mouse_motion();
		const KeyEvent* read_key();
		const WindowEvent* read_window();
	private:
		friend class Base;
		SDL_Event m_event;
		std::variant<Point, KeyEvent, WindowEvent> m_data;
		Event() = default;
		Event(SDL_Event);
	};
}
