#ifndef TETHYS_HEX_GRID_HPP
#define TETHYS_HEX_GRID_HPP

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
			sdl::Texture* texture;
		};
		HexGrid(const Hexagon&, const sdl::Renderer&);
		Point first_point() const;
		sdl::Texture to_texture() const;
	private:
		sdl::Texture m_forest;
		sdl::Texture m_mountain;
		sdl::Texture m_sea;
		std::list<Node> m_nodes;
		Point m_offset;
		Size m_size;
		std::reference_wrapper<const sdl::Renderer> m_renderer;
	};
}

#endif
