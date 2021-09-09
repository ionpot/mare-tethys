#pragma once

#include <sdl/config.hpp>
#include <sdl/context.hpp>
#include <sdl/event.hpp>
#include <sdl/point.hpp>
#include <sdl/renderer.hpp>

#include <ui/hex_grid.hpp>
#include <ui/hud.hpp>

#include <util/log.hpp>

namespace tethys {
	class Screen {
	public:
		enum class Status { ok, quit };

		Screen(const sdl::Config&, const sdl::Context&, util::Log&);

		Status handle(const sdl::Event&, const sdl::Context&);
		void render(const sdl::Renderer&) const;
		void update();

	private:
		ui::HexGrid m_hex_grid;
		ui::HUD m_hud;
		sdl::Point m_mouse_pos;

		Status handle_key(const sdl::KeyEvent&);
	};
}
