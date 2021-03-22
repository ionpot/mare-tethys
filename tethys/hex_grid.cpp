#include "hex_grid.hpp"

#include "hex_textures.hpp"
#include "hex_type.hpp"

#include <sdl/hexagon.hpp>
#include <sdl/point.hpp>
#include <sdl/renderer.hpp>
#include <sdl/size.hpp>
#include <sdl/texture.hpp>
#include <util/exception.hpp>
#include <util/int.hpp>

#include <string>
#include <vector>

namespace tethys {
	HexGrid::HexGrid(const GridFile& grid):
		m_nodes {grid.types.begin(), grid.types.end()},
		m_columns {grid.columns},
		m_rows {grid.rows},
		m_found {}
	{
		int excess = m_nodes.size() % m_columns;
		if (excess)
			throw Exception {"Excess columns: " + std::to_string(excess)};
	}

	const sdl::Point*
	HexGrid::find_point(sdl::Point p, const sdl::Hexagon& hex)
	{
		const auto* pos = &m_found.position;
		if (m_found.ok) {
			if (hex.contains(p - *pos))
				return pos;
		}
		seek(p, hex);
		return m_found.ok ? pos : nullptr;
	}

	sdl::Point
	HexGrid::find_position(Nodes_i index, const sdl::Hexagon& hex) const
	{
		auto height = hex.below().y;
		auto offset = hex.below_right();
		auto row = TETHYS_INT(index / m_columns);
		auto col = TETHYS_INT(index % m_columns);
		sdl::Point pos {col * offset.x, row * height};
		if (col % 2) {
			pos.y += offset.y;
		}
		return pos;
	}

	sdl::Size
	HexGrid::find_size(const sdl::Hexagon& hex) const
	{
		auto width = hex.width();
		auto height = hex.height();
		auto offset = hex.below_right();
		sdl::Size size {m_columns * width, m_rows * height};
		if (m_columns > 1) {
			size.width -= (m_columns - 1) * (width - offset.x);
			size.height += offset.y;
		}
		return size;
	}

	void
	HexGrid::seek(sdl::Point target, const sdl::Hexagon& hex)
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
			const sdl::Hexagon& hex) const
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
