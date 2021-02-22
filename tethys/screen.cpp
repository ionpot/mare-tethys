#include "screen.hpp"

#include "config.hpp"
#include "hex_grid.hpp"
#include "log.hpp"
#include "rgb.hpp"
#include "sdl.hpp"

namespace tethys::s {
	const struct {
		RGB border {200, 200, 200};
		RGB screen {rgb::black};
	} color;
}

namespace tethys {
	Screen::Screen(
			const Config& config,
			const sdl::Renderer& renderer,
			Log& log
	):
		m_hex {config.hex_side},
		m_grid {m_hex, renderer},
		m_border_tx {renderer.create_hex_border(m_hex, s::color.border)},
		m_grid_tx {m_grid.to_texture()},
		m_grid_pos {10, 10},
		m_renderer {renderer}
	{
		log.pair("Hexagon size", m_hex.size());
	}

	Screen::Status
	Screen::handle(sdl::Event& event)
	{
		if (event.is_keydown()) {
			return Status::quit;
		}
		return Status::ok;
	}

	void
	Screen::render() const
	{
		auto& rdr = m_renderer.get();
		rdr.set_color(sdl::RGBA::opaque(s::color.screen));
		rdr.clear();
		rdr.put(m_grid_tx, m_grid_pos);
		rdr.put(m_border_tx,
			m_grid_pos
			+ Hexagon::border_offset
			+ m_grid.first_point()
		);
		rdr.present();
	}
}
