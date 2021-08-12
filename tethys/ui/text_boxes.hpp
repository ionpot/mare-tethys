#pragma once

#include "text_box.hpp"

#include <game/hex_type.hpp>

#include <sdl/font.hpp>
#include <sdl/renderer.hpp>

#include <util/exception.hpp>

namespace tethys::ui {
	struct TextBoxes {
		TETHYS_EXCEPTION("TextBoxes")

		const TextBox agriculture;
		const TextBox city;
		const TextBox desert;
		const TextBox forest;
		const TextBox hills;
		const TextBox mountain;
		const TextBox plains;
		const TextBox sea;
		const TextBox village;

		TextBoxes(
			const TextBox::Config&,
			const sdl::Font&,
			const sdl::Renderer&);

		const TextBox* find(game::HexType) const;
	};
}
