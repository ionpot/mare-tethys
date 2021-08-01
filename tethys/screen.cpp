#include "screen.hpp"

#include "config.hpp"
#include "grid_file.hpp"
#include "grid_view.hpp"

#include <sdl/context.hpp>
#include <sdl/event.hpp>
#include <sdl/hexagon.hpp>
#include <sdl/key.hpp>
#include <sdl/rgb.hpp>

#include <util/log.hpp>

namespace tethys {
	Screen::Screen(
			const Config& config,
			const sdl::Context& sdl,
			util::Log& log
	):
		m_focus {sdl.window.has_focus()},
		m_grid_view {
			grid_file::read("tethys.grid"),
			sdl::Hexagon {config.hex_side},
			config.window_size,
			config.scroll_speed,
			sdl.renderer,
			log
		},
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
				m_grid_view.scroll.stop();
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
				m_grid_view.scroll.start_left();
			else
				m_grid_view.scroll.stop_left();
			break;
		case sdl::Key::right:
			if (event.pressed)
				m_grid_view.scroll.start_right();
			else
				m_grid_view.scroll.stop_right();
			break;
		case sdl::Key::up:
			if (event.pressed)
				m_grid_view.scroll.start_up();
			else
				m_grid_view.scroll.stop_up();
			break;
		case sdl::Key::down:
			if (event.pressed)
				m_grid_view.scroll.start_down();
			else
				m_grid_view.scroll.stop_down();
			break;
		case sdl::Key::other:
			return Status::quit;
		}
		return Status::ok;
	}

	void
	Screen::render(const sdl::Renderer& rdr) const
	{
		rdr.set_color(sdl::rgba::opaque(sdl::rgb::black));
		rdr.clear();
		m_grid_view.render(rdr);
		rdr.present();
	}

	void
	Screen::update()
	{
		m_grid_view.update(m_mouse_pos);
	}
}
