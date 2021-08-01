#pragma once

#include <game/hex_type.hpp>

#include <sdl/hexagon.hpp>
#include <sdl/renderer.hpp>
#include <sdl/texture.hpp>

#include <util/exception.hpp>

#include <functional>
#include <optional>

namespace tethys {
	struct HexTextures {
		struct Exception : public util::Exception {
			Exception(std::string text):
				util::Exception {"HexTextures", text}
			{}
		};

		typedef std::reference_wrapper<const sdl::Texture> TextureRef;

		struct Overlay {
			TextureRef texture;
			sdl::Point offset;
		};

		sdl::Texture active;
		sdl::Texture agriculture;
		sdl::Texture base;
		sdl::Texture city;
		sdl::Texture desert;
		sdl::Texture forest;
		sdl::Texture mountain;
		sdl::Texture plains;
		sdl::Texture sea;

		HexTextures(const sdl::Hexagon&, const sdl::Renderer&);
		std::optional<TextureRef> base_of(game::HexType) const;
		std::optional<Overlay> overlay_of(game::HexType) const;
	};
}
