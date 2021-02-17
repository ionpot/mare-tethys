#include "screen.hpp"

#include "config.hpp"
#include "hexagon.hpp"
#include "log.hpp"
#include "rect.hpp"
#include "rgb.hpp"
#include "sdl.hpp"

namespace tethys {
	auto create_texture(const sdl::Renderer& renderer, double hex_side)
	{
		Hexagon hex {hex_side};
		auto tx = renderer.create_target_texture(hex.size());
		renderer.set_target(tx);
		renderer.set_color(sdl::RGBA::transparent);
		renderer.clear();
		renderer.set_color(sdl::RGBA::opaque(rgb::red));
		renderer.draw_hex(hex);
		renderer.reset_target();
		return tx;
	}

	Screen::Screen(
		const Config& config,
		const sdl::Renderer& renderer,
		Log& log
	):
		m_texture {create_texture(renderer, config.hex_side)},
		m_tex_pos {100, 100},
		m_put_tex {true}
	{
		log.pair("Hexagon size", m_texture.size);
	}

	Screen::Status Screen::handle(sdl::Event& event)
	{
		if (event.is_keydown()) {
			return Status::quit;
		}
		auto mouse = event.read_mouse_motion();
		if (mouse) {
			Rect rect {m_tex_pos, m_texture.size};
			m_put_tex = !rect.contains(*mouse);
		}
		return Status::ok;
	}

	void Screen::render(const sdl::Renderer& renderer) const
	{
		renderer.set_color(sdl::RGBA::opaque(rgb::black));
		renderer.clear();
		if (m_put_tex) {
			renderer.put(m_texture, m_tex_pos);
		}
		renderer.present();
	}
}
