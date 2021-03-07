#ifndef TETHYS_SCREEN_HPP
#define TETHYS_SCREEN_HPP

#include "config.hpp"
#include "hex_grid.hpp"
#include "hex_textures.hpp"
#include "hexagon.hpp"
#include "log.hpp"
#include "point.hpp"
#include "scroll.hpp"
#include "sdl.hpp"

namespace tethys {
	class Screen {
	public:
		enum class Status { ok, quit };
		Screen(const Config&, const sdl::Context&, Log&);
		Status handle(sdl::Event&);
		void render() const;
		void update();
	private:
		const Point* m_active_point;
		bool m_focus;
		Hexagon m_hex;
		HexGrid m_grid;
		HexTextures m_hex_textures;
		sdl::Texture m_border_tx;
		sdl::Texture m_grid_tx;
		Point m_grid_pos;
		std::reference_wrapper<const sdl::Renderer> m_renderer;
		Scroll m_scroll;
		Status handle_key(const sdl::KeyEvent&);
	};
}

#endif
