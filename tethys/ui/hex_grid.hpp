#pragma once

#include "hex_textures.hpp"

#include <game/grid.hpp>
#include <game/hex_type.hpp>

#include <sdl/context.hpp>
#include <sdl/event.hpp>
#include <sdl/hexagon.hpp>
#include <sdl/hex_grid.hpp>
#include <sdl/point.hpp>
#include <sdl/renderer.hpp>
#include <sdl/scroll.hpp>
#include <sdl/size.hpp>

#include <util/grid.hpp>
#include <util/log.hpp>

#include <optional>

namespace tethys::ui {
	class HexGrid {
	public:
		HexGrid(
			game::Grid&&,
			sdl::Hexagon,
			sdl::Size view_size,
			int scroll_speed,
			const sdl::Context&,
			util::Log&);

		game::HexType active_hex_type() const;

		void on_focus_lost();
		void on_key(const sdl::KeyEvent&);

		void render(const sdl::Renderer&) const;

		void update(sdl::Point mouse_pos);

	private:
		game::Grid m_game_grid;
		sdl::HexGrid m_hex_grid;
		util::GridSize m_max_visible;
		util::GridSection m_visible_section;
		std::optional<util::GridIndex> m_active_i;
		sdl::Point m_mouse_pos;
		sdl::Point m_offset;
		sdl::Scroll m_scroll;
		HexTextures m_textures;

		util::GridIterator
			begin() const;
		std::optional<util::GridIndex>
			find_active_index(sdl::Point mouse_pos) const;
		util::GridSection
			get_visible_section(sdl::Point offset) const;
		sdl::Point
			position_of(util::GridIndex) const;
	};
}
