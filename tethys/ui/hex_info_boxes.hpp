#pragma once

#include <game/config.hpp>
#include <game/hex_type.hpp>

#include <sdl/font.hpp>
#include <sdl/renderer.hpp>
#include <sdl/text_box.hpp>
#include <sdl/text_lines_box.hpp>

#include <util/exception.hpp>

namespace tethys::ui {
	class HexInfoBoxes {
	public:
		TETHYS_EXCEPTION("HexInfoBoxes")

		HexInfoBoxes(
			const sdl::TextBox::Config&,
			const game::Config&,
			const sdl::Font&,
			const sdl::Renderer&);

		const sdl::TextLinesBox* find(game::HexType) const;

	private:
		sdl::TextLinesBox m_agriculture;
		sdl::TextLinesBox m_city;
		sdl::TextLinesBox m_desert;
		sdl::TextLinesBox m_forest;
		sdl::TextLinesBox m_hills;
		sdl::TextLinesBox m_mountain;
		sdl::TextLinesBox m_plains;
		sdl::TextLinesBox m_sea;
		sdl::TextLinesBox m_village;
	};
}
