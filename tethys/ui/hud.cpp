#include "hud.hpp"

#include "config.hpp"
#include "hex_grid.hpp"

#include <game/config.hpp>

#include <sdl/context.hpp>
#include <sdl/renderer.hpp>

namespace tethys::ui {
	HUD::HUD(
			const game::Config& game,
			const Config& ui,
			const sdl::Context& sdl
	):
		m_active_hex {},
		m_font {ui.font.create(sdl)},
		m_hex_info {ui.text_box, game, m_font, sdl.renderer}
	{}

	void
	HUD::render(const sdl::Renderer& rdr) const
	{
		if (auto box = m_hex_info.find(m_active_hex)) {
			box->render(rdr, {10});
		}
	}

	void
	HUD::update(const HexGrid& grid)
	{
		m_active_hex = grid.active_hex_type();
	}
}
