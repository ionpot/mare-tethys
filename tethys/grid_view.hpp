#pragma once

#include "hex_textures.hpp"

#include <game/grid.hpp>

#include <sdl/hexagon.hpp>
#include <sdl/hex_grid.hpp>
#include <sdl/point.hpp>
#include <sdl/renderer.hpp>
#include <sdl/scroll.hpp>
#include <sdl/size.hpp>

#include <util/exception.hpp>
#include <util/grid.hpp>
#include <util/log.hpp>

#include <optional>
#include <string>

namespace tethys {
	class GridView {
	public:
		typedef sdl::Point AbsolutePos;
		typedef sdl::Point RelativePos;

		struct Exception : public util::Exception {
			Exception(std::string text):
				util::Exception {"GridView", text}
			{}
		};

		struct Visible {
			const util::GridSize max;
			util::GridIndex start;
			util::GridIndex end;

			Visible(
				const game::Grid&,
				const sdl::HexGrid&,
				sdl::Size view_size,
				AbsolutePos offset);

			void update(AbsolutePos, const game::Grid&, const sdl::HexGrid&);
		};

		sdl::Scroll scroll;

		GridView(
			game::Grid&&,
			sdl::Hexagon,
			sdl::Size,
			const sdl::Renderer&,
			util::Log&);

		util::GridIterator begin() const;
		std::optional<util::GridIndex> index_of(AbsolutePos) const;
		void render(const sdl::Renderer&) const;
		void update(RelativePos mouse_position);
		AbsolutePos to_absolute(RelativePos) const;
		RelativePos to_relative(AbsolutePos) const;

	private:
		std::optional<util::GridIndex> m_active_i;
		RelativePos m_cached_mouse_pos;
		const game::Grid m_game_grid;
		const sdl::HexGrid m_hex_grid;
		sdl::Point m_offset;
		const HexTextures m_textures;
		Visible m_visible;
	};
}
