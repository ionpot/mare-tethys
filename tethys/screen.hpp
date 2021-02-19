#ifndef TETHYS_SCREEN_HPP
#define TETHYS_SCREEN_HPP

#include "config.hpp"
#include "hex_grid.hpp"
#include "hexagon.hpp"
#include "log.hpp"
#include "point.hpp"
#include "sdl.hpp"

namespace tethys {
	class Screen {
	public:
		enum class Status { ok, quit };
		Screen(const Config&, const sdl::Renderer&, Log&);
		Status handle(sdl::Event&);
		void render() const;
	private:
		Hexagon m_hex;
		HexGrid m_grid;
		sdl::Texture m_grid_tx;
		Point m_grid_pos;
		std::reference_wrapper<const sdl::Renderer> m_renderer;
	};
}

#endif
