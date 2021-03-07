#ifndef TETHYS_HEX_TEXTURES_HPP
#define TETHYS_HEX_TEXTURES_HPP

#include "exception.hpp"
#include "hex_type.hpp"
#include "hexagon.hpp"
#include "sdl.hpp"

namespace tethys {
	class HexTextures {
	public:
		struct Exception : public tethys::Exception {
			Exception(std::string text):
				tethys::Exception {"HexTextures", text}
			{}
		};
		HexTextures(Hexagon, const sdl::Renderer&);
		const sdl::Texture& of_type(HexType) const;
	private:
		sdl::Texture m_forest;
		sdl::Texture m_mountain;
		sdl::Texture m_sea;
	};
}

#endif
