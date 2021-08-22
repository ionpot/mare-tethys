#pragma once

#include <game/hex_type.hpp>

#include <sdl/context.hpp>
#include <sdl/hexagon.hpp>
#include <sdl/texture.hpp>

#include <util/exception.hpp>

#include <functional>
#include <optional>

namespace tethys::ui {
	struct HexTextures {
		TETHYS_EXCEPTION("HexTextures")

		struct UnknownHexType : public Exception {
			UnknownHexType(): Exception {"Unknown hex type."} {}
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
		sdl::Texture hills;
		sdl::Texture mountain;
		sdl::Texture plains;
		sdl::Texture sea;
		sdl::Texture village;

		HexTextures(const sdl::Hexagon&, const sdl::Context&);
		std::optional<TextureRef> base_of(game::HexType) const;
		std::optional<Overlay> overlay_of(game::HexType) const;
	};
}
