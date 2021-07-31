#pragma once

#include <game/hex_type.hpp>

#include <sdl/hexagon.hpp>
#include <sdl/renderer.hpp>
#include <sdl/texture.hpp>

#include <util/exception.hpp>

namespace tethys {
	struct HexTextures {
		struct Exception : public util::Exception {
			Exception(std::string text):
				util::Exception {"HexTextures", text}
			{}
		};

		sdl::Texture active;
		sdl::Texture agriculture;
		sdl::Texture city;
		sdl::Texture desert;
		sdl::Texture forest;
		sdl::Texture mountain;
		sdl::Texture plains;
		sdl::Texture sea;

		HexTextures(const sdl::Hexagon&, const sdl::Renderer&);
		const sdl::Texture& of_type(game::HexType) const;
	};
}
