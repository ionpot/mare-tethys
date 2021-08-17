#pragma once

#include <game/hex_type.hpp>

#include <sdl/font.hpp>
#include <sdl/renderer.hpp>
#include <sdl/text_box.hpp>

#include <util/exception.hpp>

namespace tethys::ui {
	struct TextBoxes {
		TETHYS_EXCEPTION("TextBoxes")

		const sdl::TextBox agriculture;
		const sdl::TextBox city;
		const sdl::TextBox desert;
		const sdl::TextBox forest;
		const sdl::TextBox hills;
		const sdl::TextBox mountain;
		const sdl::TextBox plains;
		const sdl::TextBox sea;
		const sdl::TextBox village;

		TextBoxes(
			const sdl::TextBox::Config&,
			const sdl::Font&,
			const sdl::Renderer&);

		const sdl::TextBox* find(game::HexType) const;
	};
}
