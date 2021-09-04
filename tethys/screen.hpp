#pragma once

#include <sdl/context.hpp>
#include <sdl/event.hpp>
#include <sdl/point.hpp>
#include <sdl/renderer.hpp>

#include <ui/config.hpp>
#include <ui/hex_grid.hpp>
#include <ui/hud.hpp>

#include <util/log.hpp>

namespace tethys {
	class Screen {
	public:
		enum class Status { ok, quit };

		Screen(const ui::Config&, const sdl::Context&, util::Log&);

		Status handle(const sdl::Event&);
		void render(const sdl::Renderer&) const;
		void update();

	private:
		bool m_focus;
		ui::HexGrid m_hex_grid;
		ui::HUD m_hud;
		sdl::Point m_mouse_pos;

		Status handle_key(const sdl::KeyEvent&);
	};
}
