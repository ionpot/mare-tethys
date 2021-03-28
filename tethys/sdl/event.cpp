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

	Event::Event(const SDL_Event& event)
	{
		switch (event.type) {
		case SDL_KEYDOWN:
			if (event.key.repeat == 0)
				m_data = KeyEvent {true, event.key.keysym.sym};
			break;
		case SDL_KEYUP:
			if (event.key.repeat == 0)
				m_data = KeyEvent {false, event.key.keysym.sym};
			break;
		case SDL_MOUSEMOTION: {
			auto motion = event.motion;
			m_data = MouseMoveEvent {Point {motion.x, motion.y}};
			break;
		}
		case SDL_QUIT:
			m_data = QuitEvent {};
			break;
		case SDL_WINDOWEVENT:
			m_data = WindowEvent {event.window.event};
			break;
		default:
			break;
		}
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
