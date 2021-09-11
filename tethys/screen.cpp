#include "screen.hpp"

#include "grid_file.hpp"

#include <sdl/config.hpp>
#include <sdl/context.hpp>
#include <sdl/event.hpp>
#include <sdl/hexagon.hpp>
#include <sdl/key.hpp>

#include <util/cfg_file.hpp>
#include <util/log.hpp>
#include <util/rgb.hpp>

namespace tethys {
	Screen::Screen(
			const sdl::Config& config,
			const sdl::Context& sdl,
			util::Log& log
	):
		m_hex_grid {
			grid_file::read("tethys.grid"),
			sdl::Hexagon {config.hex_side},
			config.window_size,
			config.scroll_speed,
			sdl,
			log
		},
		m_hud {util::CfgFile {"game.cfg"}, sdl}
	{}

	Screen::Status
	Screen::handle(const sdl::Event& event, const sdl::Context& context)
	{
		if (event.get<sdl::QuitEvent>()) {
			return Status::quit;
		}
		if (auto* key = event.get<sdl::KeyEvent>()) {
			if (context.window.has_focus())
				return handle_key(*key);
		}
		else if (auto* window = event.get<sdl::WindowEvent>()) {
			if (window->lost_focus())
				m_hex_grid.scroll.stop();
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
	Screen::update(const sdl::Context& ctx)
	{
		m_hex_grid.update(ctx.window.mouse_position());
		m_hud.update(m_hex_grid);
	}
}
