#include "text_boxes.hpp"

#include <game/config.hpp>
#include <game/hex_type.hpp>

#include <sdl/font.hpp>
#include <sdl/renderer.hpp>
#include <sdl/text.hpp>
#include <sdl/text_lines_box.hpp>

#include <util/string.hpp>

#include <string>
#include <vector>

namespace tethys::ui {
	namespace {
		std::vector<std::string>
		s_hex(std::string name, const game::Config::Hex& hex)
		{
			return {
				name,
				util::string::kv("Gold", hex.gold),
				util::string::kv("Industry", hex.industry),
				util::string::kv("Manpower", hex.manpower)
			};
		}

		std::vector<std::string>
		s_hex_unknown(std::string name)
		{
			return {
				name,
				util::string::kv("Gold", "?"),
				util::string::kv("Industry", "?"),
				util::string::kv("Manpower", "?")
			};
		}
	}

	TextBoxes::TextBoxes(
			const sdl::TextBox::Config& config,
			const game::Config& game,
			const sdl::Font& font,
			const sdl::Renderer& rdr
	):
		agriculture {config, font, rdr, s_hex_unknown("Agriculture")},
		city {config, font, rdr, s_hex("City", game.city)},
		desert {config, font, rdr, s_hex_unknown("Desert")},
		forest {config, font, rdr, s_hex("Forest", game.forest)},
		hills {config, font, rdr, s_hex_unknown("Hills")},
		mountain {config, font, rdr, s_hex("Mountain", game.mountain)},
		plains {config, font, rdr, s_hex("Plains", game.plains)},
		sea {config, font, rdr, s_hex("Sea", game.sea)},
		village {config, font, rdr, s_hex_unknown("Village")}
	{}

	const sdl::TextLinesBox*
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
