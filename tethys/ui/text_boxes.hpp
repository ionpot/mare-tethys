#pragma once

#include <game/config.hpp>
#include <game/hex_type.hpp>

#include <sdl/font.hpp>
#include <sdl/renderer.hpp>
#include <sdl/text_box.hpp>
#include <sdl/text_lines_box.hpp>

#include <util/exception.hpp>

namespace tethys::ui {
	struct TextBoxes {
		TETHYS_EXCEPTION("TextBoxes")

		const sdl::TextLinesBox agriculture;
		const sdl::TextLinesBox city;
		const sdl::TextLinesBox desert;
		const sdl::TextLinesBox forest;
		const sdl::TextLinesBox hills;
		const sdl::TextLinesBox mountain;
		const sdl::TextLinesBox plains;
		const sdl::TextLinesBox sea;
		const sdl::TextLinesBox village;

		TextBoxes(
			const sdl::TextBox::Config&,
			const game::Config&,
			const sdl::Font&,
			const sdl::Renderer&);

		const sdl::TextLinesBox* find(game::HexType) const;
	};
}
