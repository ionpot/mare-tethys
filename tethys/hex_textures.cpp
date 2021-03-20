#include "hex_textures.hpp"

#include "hex_type.hpp"
#include "rgb.hpp"
#include "sdl.hpp"

namespace tethys {
	namespace {
		const struct {
			RGB city {100, 100, 100};
			RGB desert {200, 200, 50};
			RGB forest {0, 75, 0};
			RGB mountain {140, 70, 20};
			RGB plains {34, 139, 34};
			RGB sea {50, 50, 200};
		} s_color;
	}

	HexTextures::HexTextures(const Hexagon& hex, const sdl::Renderer& rdr):
		m_agriculture {rdr.create_texture_from_png("hex_agriculture.png")},
		m_city {rdr.create_hex(hex, s_color.city)},
		m_desert {rdr.create_hex(hex, s_color.desert)},
		m_forest {rdr.create_hex(hex, s_color.forest)},
		m_mountain {rdr.create_hex(hex, s_color.mountain)},
		m_plains {rdr.create_texture_from_png("hex_plains.png")},
		m_sea {rdr.create_texture_from_png("hex_sea.png")}
	{}

	const sdl::Texture&
	HexTextures::of_type(HexType type) const
	{
		switch (type) {
		case HexType::none:
			throw Exception {"HexType::none has no texture."};
		case HexType::agriculture:
			return m_agriculture;
		case HexType::city:
			return m_city;
		case HexType::desert:
			return m_desert;
		case HexType::forest:
			return m_forest;
		case HexType::mountain:
			return m_mountain;
		case HexType::plains:
			return m_plains;
		case HexType::sea:
			return m_sea;
		}
		throw Exception {"Unknown hex type."};
	}
}
