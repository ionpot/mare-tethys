#pragma once

#include "key.hpp"
#include "point.hpp"

#include <SDL.h>
#include <variant>

namespace tethys::sdl {
	class KeyEvent {
	public:
		bool pressed {false};
		Key key {Key::other};
	private:
		friend class Event;
		KeyEvent(bool, SDL_Keycode);
	};

	class MouseMoveEvent {
	public:
		Point position;
	private:
		friend class Event;
		MouseMoveEvent() = default;
	};

	class QuitEvent {
	private:
		friend class Event;
		QuitEvent() = default;
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
		template<class T>
		const T* get() const
		{
			return std::get_if<T>(&m_data);
		}
	private:
		friend class Base;
		std::variant<
			std::monostate,
			KeyEvent,
			MouseMoveEvent,
			QuitEvent,
			WindowEvent
		> m_data;
		Event() = default;
		Event(const SDL_Event&);
	};
}
