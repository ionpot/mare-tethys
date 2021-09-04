#pragma once

#include "config.hpp"

#include <game/hex_type.hpp>

#include <sdl/context.hpp>
#include <sdl/event.hpp>
#include <sdl/font.hpp>
#include <sdl/point.hpp>
#include <sdl/renderer.hpp>
#include <sdl/texture.hpp>

#include <ui/hex_grid.hpp>
#include <ui/hex_info_boxes.hpp>

#include <util/log.hpp>

namespace tethys {
	class Screen {
	public:
		enum class Status { ok, quit };
		Screen(const Config&, const sdl::Context&, util::Log&);
		Status handle(const sdl::Event&);
		void render(const sdl::Renderer&) const;
		void update();
	private:
		game::HexType m_active_hex;
		bool m_focus;
		sdl::Font m_font;
		ui::HexGrid m_hex_grid;
		ui::HexInfoBoxes m_hex_info;
		sdl::Point m_mouse_pos;
		Status handle_key(const sdl::KeyEvent&);
	};
}
