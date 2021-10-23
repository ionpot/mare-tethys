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
				m_hex_grid.on_focus_lost();
		}
		return Status::ok;
	}

	Screen::Status
	Screen::handle_key(const sdl::KeyEvent& event)
	{
		switch (event.key) {
		case sdl::Key::other:
			return Status::quit;
		default:
			m_hex_grid.on_key(event);
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
