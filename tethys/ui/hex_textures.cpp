#include "hex_textures.hpp"

#include <game/hex_type.hpp>

#include <sdl/context.hpp>
#include <sdl/hexagon.hpp>

#include <util/rgb.hpp>

#define PNG(ctx, file)\
	ctx.load_png(TETHYS_ASSETS_DIR "/" file)

namespace tethys::ui {
	HexTextures::HexTextures(const sdl::Hexagon& hex, const sdl::Context& ctx):
		active {ctx.renderer.create_hex(hex, util::RGB::white)},
		agriculture {PNG(ctx, "hex_agriculture.png")},
		base {PNG(ctx, "hex_base.png")},
		city {PNG(ctx, "hex_nvillage.png")},
		desert {PNG(ctx, "hex_desert.png")},
		forest {PNG(ctx, "hex_forest.png")},
		hills {PNG(ctx, "hex_hills.png")},
		mountain {PNG(ctx, "hex_mountain.png")},
		plains {PNG(ctx, "hex_plains.png")},
		sea {PNG(ctx, "hex_sea.png")},
		village {PNG(ctx, "hex_nvillage.png")}
	{}

	std::optional<HexTextures::TextureRef> 
	HexTextures::base_of(game::HexType type) const
	{
		switch (type) {
		case game::HexType::none:
			return {};
		case game::HexType::agriculture:
			return {agriculture};
		case game::HexType::city:
		case game::HexType::village:
			return {village};
		case game::HexType::desert:
			return {desert};
		case game::HexType::forest:
		case game::HexType::hills:
		case game::HexType::mountain:
			return {base};
		case game::HexType::plains:
			return {plains};
		case game::HexType::sea:
			return {sea};
		}
		throw UnknownHexType {};
	}

	std::optional<HexTextures::Overlay> 
	HexTextures::overlay_of(game::HexType type) const
	{
		switch (type) {
		case game::HexType::forest:
			return {Overlay {forest, {0, -15}}};
		case game::HexType::hills:
			return {Overlay {hills, {0, -6}}};
		case game::HexType::mountain:
			return {Overlay {mountain, {0, -19}}};
		case game::HexType::none:
		case game::HexType::agriculture:
		case game::HexType::city:
		case game::HexType::village:
		case game::HexType::desert:
		case game::HexType::plains:
		case game::HexType::sea:
			return {};
		}
		throw UnknownHexType {};
	}
}
