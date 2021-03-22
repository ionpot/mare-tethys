#pragma once

#include "renderer.hpp"
#include "size.hpp"

#include <util/macros.hpp>

#include <SDL.h>
#include <string>

namespace tethys::sdl {
	class Window {
	public:
		Renderer create_renderer() const;
		bool has_focus() const;
	private:
		friend struct Context;
		SDL_Window* m_window;
		Window(std::string title, Size window_size);
		~Window();
		TETHYS_NO_COPY(Window)
		TETHYS_DECLARE_MOVE(Window)
	};
}
