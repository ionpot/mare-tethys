#include "text_boxes.hpp"

#include <game/hex_type.hpp>

#include <sdl/font.hpp>
#include <sdl/renderer.hpp>
#include <sdl/text_box.hpp>

namespace tethys::ui {
	TextBoxes::TextBoxes(
			const sdl::TextBox::Config& config,
			const sdl::Font& font,
			const sdl::Renderer& rdr
	):
		agriculture {config, font, rdr, "Agriculture"},
		city {config, font, rdr, "City"},
		desert {config, font, rdr, "Desert"},
		forest {config, font, rdr, "Forest"},
		hills {config, font, rdr, "Hills"},
		mountain {config, font, rdr, "Mountain"},
		plains {config, font, rdr, "Plains"},
		sea {config, font, rdr, "Sea"},
		village {config, font, rdr, "Village"}
	{}

	const sdl::TextBox*
	TextBoxes::find(game::HexType type) const
	{
		switch (type) {
		case game::HexType::none:
			return nullptr;
		case game::HexType::agriculture:
			return &agriculture;
		case game::HexType::city:
			return &city;
		case game::HexType::desert:
			return &desert;
		case game::HexType::forest:
			return &forest;
		case game::HexType::hills:
			return &hills;
		case game::HexType::mountain:
			return &mountain;
		case game::HexType::plains:
			return &plains;
		case game::HexType::sea:
			return &sea;
		case game::HexType::village:
			return &village;
		}
		throw Exception {"Unknown hex type."};
	}
}
