#ifndef TETHYS_HEX_TEXTURES_HPP
#define TETHYS_HEX_TEXTURES_HPP

#include "hex_type.hpp"
#include "hexagon.hpp"
#include "sdl.hpp"

#include <util/exception.hpp>

namespace tethys {
	class HexTextures {
	public:
		struct Exception : public util::Exception {
			Exception(std::string text):
				util::Exception {"HexTextures", text}
			{}
		};
		HexTextures(const Hexagon&, const sdl::Renderer&);
		const sdl::Texture& of_type(HexType) const;
	private:
		sdl::Texture m_agriculture;
		sdl::Texture m_city;
		sdl::Texture m_desert;
		sdl::Texture m_forest;
		sdl::Texture m_mountain;
		sdl::Texture m_plains;
		sdl::Texture m_sea;
	};
}

#endif
