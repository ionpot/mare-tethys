#include "screen.hpp"

#include "config.hpp"
#include "hex_grid.hpp"
#include "log.hpp"
#include "rgb.hpp"
#include "scroll.hpp"
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
			const sdl::Context& sdl,
			Log& log
	):
		m_active_point {nullptr},
		m_focus {sdl.window.has_focus()},
		m_hex {config.hex_side},
		m_grid {m_hex},
		m_hex_textures {m_hex, sdl.renderer},
		m_border_tx {sdl.renderer.create_hex_border(m_hex, s::color.border)},
		m_grid_tx {m_grid.to_texture(sdl.renderer, m_hex_textures)},
		m_grid_pos {100, 100},
		m_renderer {sdl.renderer},
		m_scroll {config.window_size, m_grid_tx.size, 10}
	{
		log.pair("Hexagon size", m_hex.size());
	}

	Screen::Status
	Screen::handle(sdl::Event& event)
	{
		auto key = event.read_key();
		if (key) {
			return m_focus
				? handle_key(*key)
				: Status::ok;
		}
		auto mouse = event.read_mouse_motion();
		if (mouse) {
			m_active_point = m_grid.find_point(*mouse - m_grid_pos);
			return Status::ok;
		}
		auto window = event.read_window();
		if (window) {
			if (window->got_focus()) {
				m_focus = true;
				return Status::ok;
			}
			if (window->lost_focus()) {
				m_focus = false;
				m_scroll.stop();
				return Status::ok;
			}
		}
		return Status::ok;
	}

	Screen::Status
	Screen::handle_key(const sdl::KeyEvent& event)
	{
		switch (event.key) {
		case sdl::Key::left:
			if (event.pressed)
				m_scroll.start_left();
			else
				m_scroll.stop_left();
			break;
		case sdl::Key::right:
			if (event.pressed)
				m_scroll.start_right();
			else
				m_scroll.stop_right();
			break;
		case sdl::Key::up:
			if (event.pressed)
				m_scroll.start_up();
			else
				m_scroll.stop_up();
			break;
		case sdl::Key::down:
			if (event.pressed)
				m_scroll.start_down();
			else
				m_scroll.stop_down();
			break;
		case sdl::Key::other:
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
		if (m_active_point) {
			rdr.put(m_border_tx,
				m_grid_pos
				+ Hexagon::border_offset
				+ *m_active_point
			);
		}
		rdr.present();
	}

	void
	Screen::update()
	{
		m_scroll.update(m_grid_pos);
	}
}
