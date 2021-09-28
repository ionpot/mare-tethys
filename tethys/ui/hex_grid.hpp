#pragma once

#include "hex_textures.hpp"

#include <game/grid.hpp>
#include <game/hex_type.hpp>

#include <sdl/context.hpp>
#include <sdl/hexagon.hpp>
#include <sdl/hex_grid.hpp>
#include <sdl/point.hpp>
#include <sdl/renderer.hpp>
#include <sdl/size.hpp>

#include <util/grid.hpp>

#include <optional>

namespace tethys::ui {
	class HexGrid {
	public:
		HexGrid(
			game::Grid&&,
			const util::GridSection&,
			sdl::Hexagon,
			const sdl::Context&);

		game::HexType active_hex_type() const;
		void render(const sdl::Renderer&, sdl::Point offset) const;
		sdl::Size size_in_pixels() const;

		void update_active(sdl::Point mouse_pos, sdl::Point offset);
		void update_section(const util::GridSection&);

	private:
		std::optional<util::GridIndex> m_active_i;
		game::Grid m_game_grid;
		sdl::HexGrid m_hex_grid;
		util::GridSection m_section;
		HexTextures m_textures;

		util::GridIterator begin() const;
		sdl::Point position_of(util::GridIndex, sdl::Point offset) const;
	};
}
