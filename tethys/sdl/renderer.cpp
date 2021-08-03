#include "renderer.hpp"

#include "exception.hpp"
#include "hexagon.hpp"
#include "line.hpp"
#include "point.hpp"
#include "rect.hpp"
#include "rgb.hpp"
#include "size.hpp"
#include "texture.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <array>
#include <string>

namespace tethys::sdl {
	namespace {
		const Uint32 s_flags {
			SDL_RENDERER_ACCELERATED
			| SDL_RENDERER_PRESENTVSYNC
			| SDL_RENDERER_TARGETTEXTURE
		};
	}

	Renderer::Renderer(SDL_Window* window):
		m_renderer {SDL_CreateRenderer(window, -1, s_flags)}
	{
		if (!m_renderer)
			throw Exception {};
		if (SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND))
			throw Exception {};
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

	Renderer&
	Renderer::operator=(Renderer&& from) noexcept
	{
		m_renderer = from.m_renderer;
		from.m_renderer = NULL;
		return *this;
	}

	void
	Renderer::clear() const
	{
		auto err = SDL_RenderClear(m_renderer);
		if (err)
			throw Exception {};
	}

	Texture
	Renderer::create_hex(const Hexagon& hex, const RGB& color) const
	{
		auto tx = create_target_texture(hex.size());
		set_target(tx);
		set_color(rgba::transparent);
		clear();
		set_color(rgba::opaque(color));
		draw_hex(hex);
		reset_target();
		return std::move(tx);
	}

	TargetTexture
	Renderer::create_target_texture(Size size) const
	{
		return {m_renderer, size};
	}

	void
	Renderer::draw_line(Line line) const
	{
		auto err = SDL_RenderDrawLine(
			m_renderer,
			line.start.x, line.start.y,
			line.end.x, line.end.y
		);
		if (err)
			throw Exception {};
	}

	void
	Renderer::draw_hex(const Hexagon& hex) const
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
		if (SDL_RenderDrawLines(m_renderer, points.data(), (int)points.size()))
			throw Exception {};
	}

	void
	Renderer::present() const
	{
		SDL_RenderPresent(m_renderer);
	}

	void
	Renderer::put(const Texture& texture, Point position) const
	{
		auto dst = Rect {position, texture.size}.to_sdl();
		auto err = SDL_RenderCopy(
			m_renderer, texture.m_texture, NULL, &dst
		);
		if (err)
			throw Exception {};
	}

	Texture
	Renderer::create_texture_from_png(std::string filename) const
	{
		SDL_RWops* rwops {SDL_RWFromFile(filename.c_str(), "rb")};
		if (!rwops)
			throw Exception {};
		SDL_Surface* surface {IMG_LoadPNG_RW(rwops)};
		if (!surface)
			throw Exception {IMG_GetError()};
		Texture tx {m_renderer, surface};
		SDL_FreeSurface(surface);
		SDL_RWclose(rwops);
		return tx;
	}

	void
	Renderer::reset_target() const
	{
		auto err = SDL_SetRenderTarget(m_renderer, NULL);
		if (err)
			throw Exception {};
	}

	void
	Renderer::reset_color() const
	{
		set_color(rgba::opaque(rgb::black));
	}

	void
	Renderer::set_color(RGBA color) const
	{
		auto err = SDL_SetRenderDrawColor(
			m_renderer,
			color.channels.red,
			color.channels.green,
			color.channels.blue,
			color.alpha
		);
		if (err)
			throw Exception {};
	}

	void
	Renderer::set_target(const TargetTexture& texture) const
	{
		auto err = SDL_SetRenderTarget(m_renderer, texture.m_texture);
		if (err)
			throw Exception {};
	}
}
