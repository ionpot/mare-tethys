#include "hex_textures.hpp"

#include <game/hex_type.hpp>

#include <sdl/hexagon.hpp>
#include <sdl/renderer.hpp>
#include <sdl/rgb.hpp>
#include <sdl/texture.hpp>

#define PNG(rdr, file)\
	rdr.create_texture_from_png("assets/" file)

namespace tethys {
	HexTextures::HexTextures(const sdl::Hexagon& hex, const sdl::Renderer& rdr):
		active {rdr.create_hex(hex, sdl::rgb::white)},
		agriculture {PNG(rdr, "hex_agriculture.png")},
		city {rdr.create_hex(hex, {100, 100, 100})},
		desert {rdr.create_hex(hex, {200, 200, 50})},
		forest {rdr.create_hex(hex, {0, 75, 0})},
		mountain {rdr.create_hex(hex, {140, 70, 20})},
		plains {PNG(rdr, "hex_plains.png")},
		sea {PNG(rdr, "hex_sea.png")}
	{}

	HexTextures::TextureMaybe
	HexTextures::of_type(game::HexType type) const
	{
		switch (type) {
		case game::HexType::none:
			return {};
		case game::HexType::agriculture:
			return {agriculture};
		case game::HexType::city:
			return {city};
		case game::HexType::desert:
			return {desert};
		case game::HexType::forest:
			return {forest};
		case game::HexType::mountain:
			return {mountain};
		case game::HexType::plains:
			return {plains};
		case game::HexType::sea:
			return {sea};
		}
		throw Exception {"Unknown hex type."};
	}
}
