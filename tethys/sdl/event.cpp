#include "event.hpp"

#include "key.hpp"
#include "point.hpp"

#include <SDL.h>
#include <variant>

namespace tethys::sdl {
	namespace {
		Key
		s_lookup_keycode(SDL_Keycode code)
		{
			switch (code)
			{
			case SDLK_DOWN:
				return Key::down;
			case SDLK_LEFT:
				return Key::left;
			case SDLK_RIGHT:
				return Key::right;
			case SDLK_UP:
				return Key::up;
			default:
				return Key::other;
			}
		}
	}

	Event::Event(SDL_Event event):
		m_event {event},
		m_data {}
	{}

	bool
	Event::is_quit() const
	{
		return m_event.type == SDL_QUIT;
	}

	const Point*
	Event::read_mouse_motion()
	{
		if (m_event.type == SDL_MOUSEMOTION) {
			auto motion = m_event.motion;
			m_data = Point {motion.x, motion.y};
			return std::get_if<Point>(&m_data);
		}
		return nullptr;
	}

	const KeyEvent*
	Event::read_key()
	{
		if (m_event.type == SDL_KEYDOWN && m_event.key.repeat == 0) {
			m_data = KeyEvent {true, m_event.key.keysym.sym};
			return std::get_if<KeyEvent>(&m_data);
		}
		if (m_event.type == SDL_KEYUP && m_event.key.repeat == 0) {
			m_data = KeyEvent {false, m_event.key.keysym.sym};
			return std::get_if<KeyEvent>(&m_data);
		}
		return nullptr;
	}

	const WindowEvent*
	Event::read_window()
	{
		if (m_event.type == SDL_WINDOWEVENT) {
			m_data = WindowEvent {m_event.window.event};
			return std::get_if<WindowEvent>(&m_data);
		}
		return nullptr;
	}

	// key event //

	KeyEvent::KeyEvent(bool pressed, SDL_Keycode code):
		pressed {pressed},
		key {s_lookup_keycode(code)}
	{}

	// window event //

	WindowEvent::WindowEvent(Uint8 id):
		m_id {id}
	{}

	bool
	WindowEvent::got_focus() const
	{
		return m_id == SDL_WINDOWEVENT_FOCUS_GAINED;
	}

	bool
	WindowEvent::lost_focus() const
	{
		return m_id == SDL_WINDOWEVENT_FOCUS_LOST;
	}
}
