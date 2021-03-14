#include "hex_grid.hpp"

#include "hex_textures.hpp"
#include "hex_type.hpp"
#include "hexagon.hpp"
#include "point.hpp"
#include "sdl.hpp"
#include "size.hpp"

#include <string>
#include <vector>

namespace tethys {
	HexGrid::HexGrid():
		m_nodes {{
			HexType::none,
			HexType::city,
			HexType::none,

			HexType::desert,
			HexType::sea,
			HexType::plains,

			HexType::forest,
			HexType::mountain,
			HexType::forest
		}},
		m_columns {3},
		m_rows {static_cast<int>(m_nodes.size() / m_columns)},
		m_found {}
	{
		int excess = m_nodes.size() % m_columns;
		if (excess)
			throw Exception {"Excess columns: " + std::to_string(excess)};
	}

	const Point*
	HexGrid::find_point(Point p, const Hexagon& hex)
	{
		const auto* pos = &m_found.position;
		if (m_found.ok) {
			if (hex.contains(p - *pos))
				return pos;
		}
		seek(p, hex);
		return m_found.ok ? pos : nullptr;
	}

	Point
	HexGrid::find_position(Nodes_i index, const Hexagon& hex) const
	{
		auto height = hex.below().y;
		auto offset = hex.below_right();
		int row = index / m_columns;
		int col = index % m_columns;
		Point pos {col * offset.x, row * height};
		if (col % 2) {
			pos.y += offset.y;
		}
		return pos;
	}

	Size
	HexGrid::find_size(const Hexagon& hex) const
	{
		auto width = hex.width();
		auto height = hex.height();
		auto offset = hex.below_right();
		Size size {m_columns * width, m_rows * height};
		if (m_columns > 1) {
			size.width -= (m_columns - 1) * (width - offset.x);
			size.height += offset.y;
		}
		if (m_rows > 1) {
			auto gap = hex.below().y - height;
			size.height += (m_rows - 1) * gap;
		}
		return size;
	}

	void
	HexGrid::seek(Point target, const Hexagon& hex)
	{
		for (Nodes_i i = 0; i < m_nodes.size(); ++i) {
			auto pos = find_position(i, hex);
			if (hex.contains(target - pos)) {
				m_found.ok = (m_nodes[i] != HexType::none);
				m_found.position = pos;
				return;
			}
		}
		m_found.ok = false;
	}

	sdl::Texture
	HexGrid::to_texture(
			const sdl::Renderer& rdr,
			const HexTextures& textures,
			const Hexagon& hex) const
	{
		auto tx = rdr.create_target_texture(find_size(hex));
		rdr.set_target(tx);
		for (Nodes_i i = 0; i < m_nodes.size(); ++i) {
			auto type = m_nodes[i];
			if (type == HexType::none)
				continue;
			auto pos = find_position(i, hex);
			rdr.put(textures.of_type(type), pos);
		}
		rdr.reset_target();
		return std::move(tx);
	}
}
