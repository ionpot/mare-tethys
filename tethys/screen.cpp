#include "screen.hpp"

#include "config.hpp"
#include "grid_file.hpp"
#include "hex_grid.hpp"
#include "scroll.hpp"

#include <sdl/rgb.hpp>
#include <sdl/sdl.hpp>
#include <util/log.hpp>

namespace tethys {
	namespace {
		const struct {
			sdl::RGB border {200, 200, 200};
			sdl::RGB screen {sdl::rgb::black};
		} s_color;
	}

	Screen::Screen(
			const Config& config,
			const sdl::Context& sdl,
			util::Log& log
	):
		m_active_point {nullptr},
		m_focus {sdl.window.has_focus()},
		m_hex {config.hex_side},
		m_grid {GridFile::read("tethys.grid")},
		m_hex_textures {m_hex, sdl.renderer},
		m_border_tx {sdl.renderer.create_hex(m_hex, s_color.border)},
		m_grid_tx {m_grid.to_texture(sdl.renderer, m_hex_textures, m_hex)},
		m_grid_pos {50, 50},
		m_mouse_pos {},
		m_renderer {sdl.renderer},
		m_scroll {config.window_size, m_grid_tx.size, 10}
	{
		log.pair("Hexagon size", m_hex.size().to_str());
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
		auto mouse_pos = event.read_mouse_motion();
		if (mouse_pos) {
			m_mouse_pos = *mouse_pos;
			update_active_point();
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
		rdr.set_color(sdl::RGBA::opaque(s_color.screen));
		rdr.clear();
		rdr.put(m_grid_tx, m_grid_pos);
		if (m_active_point) {
			rdr.put(m_border_tx,
				m_grid_pos
				+ *m_active_point
			);
		}
		rdr.present();
	}

	void
	Screen::update()
	{
		auto prev_pos = m_grid_pos;
		m_scroll.update(m_grid_pos);
		if (m_grid_pos != prev_pos)
			update_active_point();
	}

	void
	Screen::update_active_point()
	{
		m_active_point =
			m_grid.find_point(m_mouse_pos - m_grid_pos, m_hex);
	}
}
