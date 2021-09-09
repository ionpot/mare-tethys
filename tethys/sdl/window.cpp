#include "window.hpp"

#include "exception.hpp"
#include "event.hpp"
#include "renderer.hpp"
#include "size.hpp"

#include <SDL.h>
#include <string>

namespace tethys::sdl {
	namespace {
		SDL_Window*
		s_create_window(
				std::string title,
				Size size,
				Window::Flags flags = 0)
		{
			return SDL_CreateWindow(
				title.c_str(),
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				size.width, size.height,
				flags
			);
		}
	}

	Window::Window(std::string title, Size size):
		m_focus {false},
		m_window {s_create_window(title, size)}
	{
		if (!m_window)
			throw Exception {};
		m_focus = check_flags(SDL_WINDOW_INPUT_FOCUS);
	}

	Window::~Window()
	{
		if (m_window) {
			SDL_DestroyWindow(m_window);
			m_window = NULL;
		}
	}

	bool
	Window::check_flags(Flags flags) const
	{
		auto active = SDL_GetWindowFlags(m_window);
		return active & flags;
	}

	Renderer
	Window::create_renderer() const
	{
		return Renderer {m_window};
	}

	void
	Window::handle(const Event& event)
	{
		if (auto* window = event.get<WindowEvent>()) {
			if (window->got_focus())
				m_focus = true;
			else if (window->lost_focus())
				m_focus = false;
		}
	}

	bool
	Window::has_focus() const
	{
		return m_focus;
	}
}
