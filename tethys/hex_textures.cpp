#include "hex_textures.hpp"

#include "hex_type.hpp"
#include "rgb.hpp"
#include "sdl.hpp"

namespace tethys::s {
	const struct {
		RGB forest {50, 200, 50};
		RGB mountain {100, 100, 100};
		RGB sea {50, 50, 200};
	} color;
}

namespace tethys {
	HexTextures::HexTextures(Hexagon hex, const sdl::Renderer& rdr):
		m_forest {rdr.create_hex(hex, s::color.forest)},
		m_mountain {rdr.create_hex(hex, s::color.mountain)},
		m_sea {rdr.create_hex(hex, s::color.sea)}
	{}

	const sdl::Texture&
	HexTextures::of_type(HexType type) const
	{
		switch (type) {
		case HexType::none:
			throw Exception {"HexType::none has no texture."};
		case HexType::forest:
			return m_forest;
		case HexType::mountain:
			return m_mountain;
		case HexType::sea:
			return m_sea;
		}
	}
}
