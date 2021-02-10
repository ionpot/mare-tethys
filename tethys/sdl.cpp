#include "sdl.hpp"

#include "log.hpp"

#include <SDL.h>
#include <string>

namespace tethys::sdl::s {
	bool initialized = false;
	Uint32 renderer_flags =
		SDL_RENDERER_ACCELERATED
		| SDL_RENDERER_PRESENTVSYNC;

	SDL_Window* create_window(
		const std::string title,
		Window::Size size,
		Uint32 flags
	) {
		return SDL_CreateWindow(
			title.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			size.width, size.height,
			flags
		);
	}
}

namespace tethys::sdl {
	Base::Base(Log& log):
		m_call_quit {true}, m_event {}, m_log {log}
	{
		if (s::initialized)
			throw Exception {"Cannot re-initialize."};
		log.put("Initializing SDL...");
		int error = SDL_Init(SDL_INIT_VIDEO);
		s::initialized = !error;
		if (error) {
			std::string text {SDL_GetError()};
			SDL_Quit();
			throw Exception {text};
		}
	}

	Base::~Base()
	{
		if (m_call_quit) {
			m_log.get().put("Quitting SDL...");
			SDL_Quit();
			s::initialized = false;
		}
	}

	Base::Base(Base&& from) noexcept:
		m_call_quit {true},
		m_event {from.m_event},
		m_log {from.m_log}
	{
		from.m_call_quit = false;
	}

	Base& Base::operator=(Base&& from) noexcept
	{
		m_call_quit = true;
		from.m_call_quit = false;
		m_event = from.m_event;
		m_log = from.m_log;
		return *this;
	}
	
	void Base::delay(Uint32 milliseconds)
	{
		SDL_Delay(milliseconds);
	}

	Event* Base::poll_event()
	{
		SDL_Event event;
		if (SDL_PollEvent(&event)) {
			m_event = Event {event};
			return &m_event;
		}
		return nullptr;
	}

	// context //

	Context::Context(const std::string title, Window::Size size, Log& log):
		base {log}, window {title, size, log}, renderer {window.create_renderer()}
	{}

	// event //

	Event::Event(SDL_Event event):
		m_event {event}
	{}

	bool Event::is_quit()
	{
		return m_event.type == SDL_QUIT;
	}

	// renderer //

	Renderer::Renderer(SDL_Window* window):
		m_renderer {SDL_CreateRenderer(window, -1, s::renderer_flags)}
	{
		if (!m_renderer)
			throw Exception {SDL_GetError()};
	}

	Renderer::~Renderer()
	{
		if (m_renderer) {
			SDL_DestroyRenderer(m_renderer);
		}
	}

	Renderer::Renderer(Renderer&& from) noexcept:
		m_renderer {from.m_renderer}
	{
		from.m_renderer = NULL;
	}

	Renderer& Renderer::operator=(Renderer&& from) noexcept
	{
		m_renderer = from.m_renderer;
		from.m_renderer = NULL;
		return *this;
	}

	void Renderer::clear()
	{
		SDL_RenderClear(m_renderer);
	}

	void Renderer::present()
	{
		SDL_RenderPresent(m_renderer);
	}

	// window //

	Window::Window(const std::string title, Size size, Log& log):
		m_window {NULL}
	{
		log.put("Trying Vulkan window...");
		m_window = s::create_window(title, size, SDL_WINDOW_VULKAN);
		if (m_window)
			return;
		log.put("Trying Metal window...");
		m_window = s::create_window(title, size, SDL_WINDOW_METAL);
		if (m_window)
			return;
		log.put("Trying OpenGL window...");
		m_window = s::create_window(title, size, SDL_WINDOW_OPENGL);
		if (m_window)
			return;
		throw Exception {SDL_GetError()};
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

	Window& Window::operator=(Window&& from) noexcept
	{
		m_window = from.m_window;
		from.m_window = NULL;
		return *this;
	}

	Renderer Window::create_renderer()
	{
		return Renderer {m_window};
	}
}
