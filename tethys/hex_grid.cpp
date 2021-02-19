#include "hex_grid.hpp"

#include "hexagon.hpp"
#include "point.hpp"
#include "rgb.hpp"
#include "sdl.hpp"
#include "size.hpp"

namespace tethys::s {
	const struct {
		RGB forest {50, 200, 50};
		RGB mountain {100, 100, 100};
		RGB sea {50, 50, 200};
	} color;

	auto
	create_texture(
			const sdl::Renderer& rdr,
			const Hexagon& hex,
			const RGB& rgb)
	{
		auto tx = rdr.create_target_texture(hex.size());
		rdr.set_target(tx);
		rdr.set_color(sdl::RGBA::transparent);
		rdr.clear();
		rdr.set_color(sdl::RGBA::opaque(rgb));
		rdr.draw_hex(hex);
		rdr.reset_target();
		return tx;
	}

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
	HexGrid::HexGrid(const Hexagon& hex, const sdl::Renderer& rdr):
		m_forest {s::create_texture(rdr, hex, s::color.forest)},
		m_mountain {s::create_texture(rdr, hex, s::color.mountain)},
		m_sea {s::create_texture(rdr, hex, s::color.sea)},
		m_nodes {
			{Point {}, &m_sea},
			{hex.above(), &m_mountain},
			{hex.above_left(), &m_forest},
			{hex.above_right(), &m_forest}
		},
		m_offset {s::find_offset(m_nodes)},
		m_size {s::find_size(m_nodes, hex, m_offset)},
		m_renderer {rdr}
	{}

	sdl::Texture
	HexGrid::to_texture() const
	{
		auto& rdr = m_renderer.get();
		auto tx = rdr.create_target_texture(m_size);
		rdr.set_target(tx);
		for (const auto& node : m_nodes) {
			rdr.put(*node.texture, m_offset + node.position);
		}
		rdr.reset_target();
		return tx;
	}
}
