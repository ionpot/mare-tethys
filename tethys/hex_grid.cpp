#include "hex_grid.hpp"

#include "hex_textures.hpp"
#include "hex_type.hpp"
#include "hexagon.hpp"
#include "point.hpp"
#include "rect.hpp"
#include "sdl.hpp"
#include "size.hpp"

#include <list>

namespace tethys::s {
	Point
	find_offset(const std::list<HexGrid::Node>& nodes)
	{
		Point offset;
		for (const auto& node : nodes) {
			offset.pick_min(node.position);
		}
		return offset.negate();
	}

	Size
	find_size(
			const std::list<HexGrid::Node>& nodes,
			const Hexagon& hex,
			Point offset)
	{
		Point p;
		for (const auto& node : nodes) {
			p.pick_max(node.position);
		}
		p += offset;
		return Size {p.x, p.y} + hex.size();
	}
}

namespace tethys {
	HexGrid::HexGrid(Hexagon hex):
		m_hex {hex},
		m_nodes {
			{Point {}, HexType::sea},
			{hex.above(), HexType::mountain},
			{hex.above_left(), HexType::forest},
			{hex.above_right(), HexType::forest},
			{hex.below(), HexType::mountain},
			{hex.below_left(), HexType::forest},
			{hex.below_right(), HexType::forest}
		},
		m_offset {s::find_offset(m_nodes)},
		m_size {s::find_size(m_nodes, hex, m_offset)}
	{
		for (auto& node : m_nodes)
			node.position += m_offset;
	}

	const Point*
	HexGrid::find_point(Point p) const
	{
		Rect rect {m_size};
		if (rect.contains(p)) {
			for (const auto& node : m_nodes) {
				if (m_hex.contains(p - node.position)) {
					return &node.position;
				}
			}
		}
		return nullptr;
	}

	sdl::Texture
	HexGrid::to_texture(
			const sdl::Renderer& rdr,
			const HexTextures& textures) const
	{
		auto tx = rdr.create_target_texture(m_size);
		rdr.set_target(tx);
		for (const auto& node : m_nodes) {
			rdr.put(textures.of_type(node.type), node.position);
		}
		rdr.reset_target();
		return std::move(tx);
	}
}
