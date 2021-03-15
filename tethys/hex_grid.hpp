#ifndef TETHYS_HEX_GRID_HPP
#define TETHYS_HEX_GRID_HPP

#include "exception.hpp"
#include "grid_file.hpp"
#include "hex_textures.hpp"
#include "hex_type.hpp"
#include "hexagon.hpp"
#include "point.hpp"
#include "sdl.hpp"
#include "size.hpp"

#include <string>
#include <vector>

namespace tethys {
	class HexGrid {
	public:
		struct Exception : public tethys::Exception {
			Exception(std::string text):
				tethys::Exception {"HexGrid", text}
			{}
		};
		HexGrid(const GridFile&);
		const Point* find_point(Point, const Hexagon&);
		Size find_size(const Hexagon&) const;
		sdl::Texture to_texture(
				const sdl::Renderer&,
				const HexTextures&,
				const Hexagon&) const;
	private:
		typedef std::vector<HexType> Nodes;
		typedef Nodes::size_type Nodes_i;
		struct Found {
			bool ok {true};
			Point position {0, 0};
		};
		const Nodes m_nodes;
		const int m_columns;
		const int m_rows;
		Found m_found;
		Point find_position(Nodes_i, const Hexagon&) const;
		void seek(Point, const Hexagon&);
	};
}

#endif
