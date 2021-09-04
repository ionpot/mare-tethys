#include "screen.hpp"

#include "grid_file.hpp"

#include <sdl/context.hpp>
#include <sdl/event.hpp>
#include <sdl/hexagon.hpp>
#include <sdl/key.hpp>

#include <util/rgb.hpp>
#include <util/log.hpp>

namespace tethys {
	Screen::Screen(
			const Config& config,
			const sdl::Context& sdl,
			util::Log& log
	):
		m_focus {sdl.window.has_focus()},
		m_hex_grid {
			grid_file::read("tethys.grid"),
			sdl::Hexagon {config.ui.hex_side},
			config.ui.window_size,
			config.ui.scroll_speed,
			sdl,
			log
		},
		m_hud {config.game, config.ui, sdl},
		m_mouse_pos {}
	{}

	Screen::Status
	Screen::handle(const sdl::Event& event)
	{
		if (event.get<sdl::QuitEvent>()) {
			return Status::quit;
		}
		if (auto* key = event.get<sdl::KeyEvent>()) {
			if (m_focus)
				return handle_key(*key);
		}
		else if (auto* mouse = event.get<sdl::MouseMoveEvent>()) {
			m_mouse_pos = mouse->position;
		}
		else if (auto* window = event.get<sdl::WindowEvent>()) {
			if (window->got_focus()) {
				m_focus = true;
			}
			else if (window->lost_focus()) {
				m_focus = false;
				m_hex_grid.scroll.stop();
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
				m_hex_grid.scroll.start_left();
			else
				m_hex_grid.scroll.stop_left();
			break;
		case sdl::Key::right:
			if (event.pressed)
				m_hex_grid.scroll.start_right();
			else
				m_hex_grid.scroll.stop_right();
			break;
		case sdl::Key::up:
			if (event.pressed)
				m_hex_grid.scroll.start_up();
			else
				m_hex_grid.scroll.stop_up();
			break;
		case sdl::Key::down:
			if (event.pressed)
				m_hex_grid.scroll.start_down();
			else
				m_hex_grid.scroll.stop_down();
			break;
		case sdl::Key::other:
			return Status::quit;
		}
		return Status::ok;
	}

	void
	Screen::render(const sdl::Renderer& rdr) const
	{
		rdr.set_color(util::RGB::black);
		rdr.clear();
		m_hex_grid.render(rdr);
		m_hud.render(rdr);
		rdr.present();
	}

	void
	Screen::update()
	{
		m_hex_grid.update(m_mouse_pos);
		m_hud.update(m_hex_grid);
	}
}
