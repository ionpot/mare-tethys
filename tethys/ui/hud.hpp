#pragma once

#include "hex_grid.hpp"
#include "hex_info_boxes.hpp"

#include <game/config.hpp>
#include <game/hex_type.hpp>

#include <sdl/config.hpp>
#include <sdl/context.hpp>
#include <sdl/renderer.hpp>

namespace tethys::ui {
	class HUD {
	public:
		HUD(const game::Config&, const sdl::Config&, const sdl::Context&);

		void render(const sdl::Renderer&) const;
		void update(const HexGrid&);

	private:
		game::HexType m_active_hex;
		HexInfoBoxes m_hex_info;
	};
}
