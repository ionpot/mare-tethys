#ifndef TETHYS_HEX_GRID_HPP
#define TETHYS_HEX_GRID_HPP

#include "hex_textures.hpp"
#include "hex_type.hpp"
#include "hexagon.hpp"
#include "point.hpp"
#include "sdl.hpp"
#include "size.hpp"

#include <list>

namespace tethys {
	class HexGrid {
	public:
		struct Node {
			Point position;
			HexType type;
		};
		HexGrid(Hexagon);
		const Point* find_point(Point) const;
		sdl::Texture to_texture(const sdl::Renderer&, const HexTextures&) const;
	private:
		Hexagon m_hex;
		std::list<Node> m_nodes;
		Point m_offset;
		Size m_size;
	};
}

#endif
