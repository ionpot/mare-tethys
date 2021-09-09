#pragma once

#include "event.hpp"
#include "renderer.hpp"
#include "size.hpp"

#include <util/macros.hpp>

#include <SDL.h>
#include <string>

namespace tethys::sdl {
	class Window {
	public:
		typedef Uint32 Flags;

		bool has_focus() const;

	private:
		friend struct Context;

		bool m_focus;
		SDL_Window* m_window;

		Window(std::string title, Size window_size);
		~Window();
		TETHYS_NO_COPY(Window)

		bool check_flags(Flags) const;
		Renderer create_renderer() const;
		void handle(const Event&);
	};
}
