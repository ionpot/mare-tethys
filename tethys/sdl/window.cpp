#include "window.hpp"

#include "exception.hpp"
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
				Uint32 flags = 0)
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
		m_window {NULL}
	{
		m_window = s_create_window(title, size);
		if (!m_window) {
			throw Exception {SDL_GetError()};
		}
	}

	Window::~Window()
	{
		if (m_window) {
			SDL_DestroyWindow(m_window);
		}
	}

	Window::Window(Window&& from) noexcept:
		m_window {from.m_window}
	{
		from.m_window = NULL;
	}

	Window&
	Window::operator=(Window&& from) noexcept
	{
		m_window = from.m_window;
		from.m_window = NULL;
		return *this;
	}

	Renderer
	Window::create_renderer() const
	{
		return Renderer {m_window};
	}

	bool
	Window::has_focus() const
	{
		auto flags = SDL_GetWindowFlags(m_window);
		return flags & SDL_WINDOW_INPUT_FOCUS;
	}
}
