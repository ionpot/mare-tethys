#ifndef TETHYS_HEX_GRID_HPP
#define TETHYS_HEX_GRID_HPP

#include "grid_file.hpp"
#include "hex_textures.hpp"
#include "hex_type.hpp"

#include <sdl/hexagon.hpp>
#include <sdl/point.hpp>
#include <sdl/sdl.hpp>
#include <sdl/size.hpp>
#include <util/exception.hpp>

#include <string>
#include <vector>

namespace tethys {
	class HexGrid {
	public:
		struct Exception : public util::Exception {
			Exception(std::string text):
				util::Exception {"HexGrid", text}
			{}
		};
		HexGrid(const GridFile&);
		const sdl::Point* find_point(sdl::Point, const sdl::Hexagon&);
		sdl::Size find_size(const sdl::Hexagon&) const;
		sdl::Texture to_texture(
				const sdl::Renderer&,
				const HexTextures&,
				const sdl::Hexagon&) const;
	private:
		typedef std::vector<HexType> Nodes;
		typedef Nodes::size_type Nodes_i;
		struct Found {
			bool ok {true};
			sdl::Point position {0, 0};
		};
		const Nodes m_nodes;
		const int m_columns;
		const int m_rows;
		Found m_found;
		sdl::Point find_position(Nodes_i, const sdl::Hexagon&) const;
		void seek(sdl::Point, const sdl::Hexagon&);
	};
}

#endif
