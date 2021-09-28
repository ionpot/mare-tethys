#include "hex_grid.hpp"

#include <game/grid.hpp>
#include <game/hex_type.hpp>

#include <sdl/context.hpp>
#include <sdl/hexagon.hpp>
#include <sdl/point.hpp>
#include <sdl/renderer.hpp>
#include <sdl/size.hpp>

#include <util/grid.hpp>

#include <utility>

#define CLAMP(section, grid)\
	section.clamp(grid.size())

namespace tethys::ui {
	HexGrid::HexGrid(
			game::Grid&& grid,
			const util::GridSection& section,
			sdl::Hexagon hex,
			const sdl::Context& sdl
	):
		m_active_i {},
		m_game_grid {std::move(grid)},
		m_hex_grid {hex},
		m_section {CLAMP(section, m_game_grid)},
		m_textures {hex, sdl}
	{}

	game::HexType
	HexGrid::active_hex_type() const
	{
		return m_active_i
			? m_game_grid.cell(*m_active_i)
			: game::HexType::none;
	}

	util::GridIterator
	HexGrid::begin() const
	{
		return m_game_grid.begin(m_section);
	}

	sdl::Point
	HexGrid::position_of(util::GridIndex i, sdl::Point offset) const
	{
		return m_hex_grid.position_of(i) - offset;
	}

	void
	HexGrid::render(const sdl::Renderer& rdr, sdl::Point offset) const
	{
		for (auto iter = begin(); iter.valid(); iter.next()) {
			auto type = m_game_grid.cell(iter);
			if (auto base = m_textures.base_of(type)) {
				auto pos = position_of(iter.index(), offset);
				rdr.put(*base, pos);
			}
		}
		if (m_active_i) {
			auto i = *m_active_i;
			auto type = m_game_grid.cell(i);
			if (auto base = m_textures.base_of(type)) {
				auto pos = position_of(i, offset);
				rdr.put(m_textures.active, pos);
			}
		}
		for (auto iter = begin(); iter.valid(); iter.next()) {
			auto type = m_game_grid.cell(iter);
			if (auto overlay = m_textures.overlay_of(type)) {
				auto pos = position_of(iter.index(), offset);
				rdr.put(overlay->texture, pos + overlay->offset);
			}
		}
	}

	sdl::Size
	HexGrid::size_in_pixels() const
	{
		return m_hex_grid.size_of(m_game_grid.size());
	}

	void
	HexGrid::update_active(sdl::Point mouse_pos, sdl::Point offset)
	{
		auto pos = offset + mouse_pos;
		if (m_active_i) {
			if (m_hex_grid.contains(pos, *m_active_i))
				return;
		}
		for (auto iter = begin(); iter.valid(); iter.next()) {
			auto i = iter.index();
			if (m_hex_grid.contains(pos, i)) {
				m_active_i = i;
				return;
			}
		}
	}

	void
	HexGrid::update_section(const util::GridSection& section)
	{
		m_section = CLAMP(section, m_game_grid);
	}
}
