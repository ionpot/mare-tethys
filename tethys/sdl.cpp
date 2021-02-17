#include "sdl.hpp"

#include "exception.hpp"
#include "hexagon.hpp"
#include "line.hpp"
#include "log.hpp"
#include "point.hpp"
#include "rgb.hpp"
#include "size.hpp"

#include <SDL.h>
#include <array>
#include <string>

namespace tethys::sdl::s {
	Uint32 init_flags = SDL_INIT_VIDEO;

	Uint32 renderer_flags =
		SDL_RENDERER_ACCELERATED
		| SDL_RENDERER_PRESENTVSYNC
		| SDL_RENDERER_TARGETTEXTURE;

	Uint32 texture_format =
		SDL_PIXELFORMAT_RGBA8888;

	SDL_Window* create_window(
		const std::string title,
		Size size,
		Uint32 flags = 0
	) {
		return SDL_CreateWindow(
			title.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			size.width, size.height,
			flags
		);
	}

	SDL_Rect to_rect(Point pos, Size size)
	{
		SDL_Rect rect;
		rect.x = pos.x;
		rect.y = pos.y;
		rect.w = size.width;
		rect.h = size.height;
		return rect;
	}
}

namespace tethys::sdl {
	Base::Base(Log& log):
		m_call_quit {true},
		m_event {},
		m_log {log}
	{
		if (SDL_WasInit(s::init_flags))
			throw Exception {"Cannot re-initialize."};
		log.put("Initializing SDL...");
		int error = SDL_Init(s::init_flags);
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
	
	void Base::delay(Uint32 milliseconds) const
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

	Context::Context(const std::string title, Size size, Log& log):
		base {log},
		window {title, size},
		renderer {window.create_renderer()}
	{}

	// event //

	Event::Event(SDL_Event event):
		m_event {event}
	{}

	bool Event::is_keydown() const
	{
		return m_event.type == SDL_KEYDOWN;
	}

	bool Event::is_quit() const
	{
		return m_event.type == SDL_QUIT;
	}

	// renderer //

	Renderer::Renderer(SDL_Window* window):
		m_renderer {SDL_CreateRenderer(window, -1, s::renderer_flags)}
	{
		if (!m_renderer)
			throw Exception {SDL_GetError()};
		if (SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND))
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

	void Renderer::clear() const
	{
		auto err = SDL_RenderClear(m_renderer);
		if (err)
			throw Exception {SDL_GetError()};
	}

	TargetTexture Renderer::create_target_texture(Size size) const
	{
		return {m_renderer, size};
	}

	void Renderer::draw_line(Line line) const
	{
		auto err = SDL_RenderDrawLine(
			m_renderer,
			line.start.x, line.start.y,
			line.end.x, line.end.y
		);
		if (err)
			throw Exception {SDL_GetError()};
	}

	void Renderer::draw_hex(Hexagon hex) const
	{
		std::array points = {
			hex.point1().to_sdl(),
			hex.point2().to_sdl(),
			hex.point3().to_sdl(),
			hex.point4().to_sdl(),
			hex.point5().to_sdl(),
			hex.point6().to_sdl(),
			hex.point1().to_sdl()
		};
		if (SDL_RenderDrawLines(m_renderer, points.data(), points.size()))
			throw Exception {SDL_GetError()};
	}

	void Renderer::present() const
	{
		SDL_RenderPresent(m_renderer);
	}

	void Renderer::put(const Texture& texture, Point position) const
	{
		auto dst = s::to_rect(position, texture.size);
		auto err = SDL_RenderCopy(
			m_renderer, texture.m_texture, NULL, &dst
		);
		if (err)
			throw Exception {SDL_GetError()};
	}

	void Renderer::reset_target() const
	{
		auto err = SDL_SetRenderTarget(m_renderer, NULL);
		if (err)
			throw Exception {SDL_GetError()};
	}

	void Renderer::reset_color() const
	{
		set_color(RGBA::opaque(rgb::black));
	}

	void Renderer::set_color(RGBA color) const
	{
		auto err = SDL_SetRenderDrawColor(
			m_renderer,
			color.channels.red,
			color.channels.green,
			color.channels.blue,
			color.alpha
		);
		if (err)
			throw Exception {SDL_GetError()};
	}

	void Renderer::set_target(const TargetTexture& texture) const
	{
		auto err = SDL_SetRenderTarget(m_renderer, texture.m_texture);
		if (err)
			throw Exception {SDL_GetError()};
	}

	// rgba //

	const RGBA RGBA::transparent {rgb::black, SDL_ALPHA_TRANSPARENT};

	RGBA RGBA::opaque(RGB channels)
	{
		return {channels, SDL_ALPHA_OPAQUE};
	}

	// texture //

	Texture::Texture(SDL_Renderer* renderer, Size size, Uint32 flags):
		size {size},
		m_texture {SDL_CreateTexture(
			renderer,
			s::texture_format,
			flags,
			size.width, size.height
		)}
	{
		if (!m_texture)
			throw Exception {SDL_GetError()};
		if (SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND))
			throw Exception {SDL_GetError()};
	}

	Texture::~Texture()
	{
		if (m_texture) {
			SDL_DestroyTexture(m_texture);
		}
	}

	Texture::Texture(Texture&& from) noexcept:
		size {from.size},
		m_texture {from.m_texture}
	{
		from.m_texture = NULL;
	}

	Texture& Texture::operator=(Texture&& from) noexcept
	{
		size = from.size;
		m_texture = from.m_texture;
		from.m_texture = NULL;
		return *this;
	}

	TargetTexture::TargetTexture(SDL_Renderer* renderer, Size size):
		Texture {renderer, size, SDL_TEXTUREACCESS_TARGET}
	{}

	// window //

	Window::Window(const std::string title, Size size):
		m_window {NULL}
	{
		m_window = s::create_window(title, size);
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

	Window& Window::operator=(Window&& from) noexcept
	{
		m_window = from.m_window;
		from.m_window = NULL;
		return *this;
	}

	Renderer Window::create_renderer() const
	{
		return Renderer {m_window};
	}
}
