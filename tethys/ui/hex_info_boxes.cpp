#include "hex_info_boxes.hpp"

#include <game/bonus.hpp>
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
		std::string
		s_kv(std::string key)
		{
			return util::string::kv(key, "?");
		}

		std::string
		s_kv(std::string key, const game::Bonus& bonus)
		{
			return util::string::kv(key, bonus.to_string());
		}

		std::vector<std::string>
		s_hex(std::string name, const game::Config::Hex& hex)
		{
			return {
				name,
				s_kv("Gold", hex.gold),
				s_kv("Industry", hex.industry),
				s_kv("Manpower", hex.manpower)
			};
		}

		std::vector<std::string>
		s_hex_unknown(std::string name)
		{
			return {
				name,
				s_kv("Gold"),
				s_kv("Industry"),
				s_kv("Manpower")
			};
		}
	}

	HexInfoBoxes::HexInfoBoxes(
			const sdl::TextBox::Config& config,
			const game::Config& game,
			const sdl::Font& font,
			const sdl::Renderer& rdr
	):
		m_agriculture {config, font, rdr, s_hex_unknown("Agriculture")},
		m_city {config, font, rdr, s_hex("City", game.city)},
		m_desert {config, font, rdr, s_hex_unknown("Desert")},
		m_forest {config, font, rdr, s_hex("Forest", game.forest)},
		m_hills {config, font, rdr, s_hex_unknown("Hills")},
		m_mountain {config, font, rdr, s_hex("Mountain", game.mountain)},
		m_plains {config, font, rdr, s_hex("Plains", game.plains)},
		m_sea {config, font, rdr, s_hex("Sea", game.sea)},
		m_village {config, font, rdr, s_hex_unknown("Village")}
	{}

	const sdl::TextLinesBox*
	HexInfoBoxes::find(game::HexType type) const
	{
		switch (type) {
		case game::HexType::none:
			return nullptr;
		case game::HexType::agriculture:
			return &m_agriculture;
		case game::HexType::city:
			return &m_city;
		case game::HexType::desert:
			return &m_desert;
		case game::HexType::forest:
			return &m_forest;
		case game::HexType::hills:
			return &m_hills;
		case game::HexType::mountain:
			return &m_mountain;
		case game::HexType::plains:
			return &m_plains;
		case game::HexType::sea:
			return &m_sea;
		case game::HexType::village:
			return &m_village;
		}
		throw Exception {"Unknown hex type."};
	}
}
