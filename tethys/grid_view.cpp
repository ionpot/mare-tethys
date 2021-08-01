#include "grid_view.hpp"

#include <game/grid.hpp>

#include <sdl/hexagon.hpp>
#include <sdl/hex_grid.hpp>
#include <sdl/point.hpp>
#include <sdl/renderer.hpp>
#include <sdl/size.hpp>

#include <util/grid.hpp>
#include <util/log.hpp>

#include <optional>
#include <tuple>
#include <utility>

namespace tethys {
	namespace {
		typedef GridView::AbsolutePos Absolute;
		typedef GridView::RelativePos Relative;
	}

	// grid view visible
	GridView::Visible::Visible(
			const game::Grid& game_grid,
			const sdl::HexGrid& hex_grid,
			sdl::Size view_size,
			Absolute offset
	):
		max {hex_grid.max_visible(view_size)},
		start {},
		end {}
	{
		update(offset, game_grid, hex_grid);
	}

	void
	GridView::Visible::update(
			Absolute position,
			const game::Grid& game_grid,
			const sdl::HexGrid& hex_grid)
	{
		start = game_grid.size.clamp(hex_grid.get_visible_index(position));
		end = game_grid.size.clamp(start + max.to_index());
	}

	// grid view
	GridView::GridView(
			game::Grid&& grid,
			sdl::Hexagon hex,
			sdl::Size view_size,
			int scroll_speed,
			const sdl::Renderer& rdr,
			util::Log& log
	):
		scroll {
			view_size,
			sdl::HexGrid::calculate_size(hex, grid.size),
			scroll_speed
		},
		m_active_i {},
		m_cached_mouse_pos {},
		m_game_grid {std::move(grid)},
		m_hex_grid {hex},
		m_offset {},
		m_textures {hex, rdr},
		m_visible {m_game_grid, m_hex_grid, view_size, m_offset}
	{
		log.pair("Hex size", hex.size().to_str());
		log.pair("Grid size",
			m_game_grid.size.to_str()
			+ " (" + m_hex_grid.size_of(m_game_grid.size).to_str() + ")"
		);
		log.pair("Max visible cells", m_visible.max.to_str());
		log.pair("Scroll", scroll.to_str());
	}

	util::GridIterator
	GridView::begin() const
	{
		return m_game_grid.begin(m_visible.start, m_visible.end);
	}

	std::optional<util::GridIndex>
	GridView::index_of(Absolute position) const
	{
		if (m_active_i) {
			if (m_hex_grid.contains(position, *m_active_i))
				return m_active_i;
		}
		for (auto iter = begin(); iter.valid(); iter.next()) {
			auto i = iter.index();
			if (m_hex_grid.contains(position, i))
				return {i};
		}
		return {};
	}

	Relative
	GridView::position_of(util::GridIndex i) const
	{
		return to_relative(m_hex_grid.position_of(i));
	}

	void
	GridView::render(const sdl::Renderer& rdr) const
	{
		for (auto iter = begin(); iter.valid(); iter.next()) {
			auto i = iter.index();
			auto type = m_game_grid.cell(iter);
			if (auto base = m_textures.base_of(type)) {
				auto pos = position_of(i);
				rdr.put(*base, pos);
			}
		}
		if (m_active_i) {
			auto i = *m_active_i;
			auto type = m_game_grid.cell(i);
			if (auto base = m_textures.base_of(type)) {
				auto pos = position_of(i);
				rdr.put(m_textures.active, pos);
			}
		}
		for (auto iter = begin(); iter.valid(); iter.next()) {
			auto i = iter.index();
			auto type = m_game_grid.cell(iter);
			if (auto overlay = m_textures.overlay_of(type)) {
				auto pos = position_of(i);
				rdr.put(overlay->texture, pos + overlay->offset);
			}
		}
	}

	void
	GridView::update(Relative mouse_pos)
	{
		auto pos = scroll.next(m_offset);
		auto offset_updated = pos != m_offset;
		if (offset_updated) {
			m_offset = pos;
			m_visible.update(pos.negate(), m_game_grid, m_hex_grid);
		}
		auto mouse_updated = mouse_pos != m_cached_mouse_pos;
		if (mouse_updated) {
			m_cached_mouse_pos = mouse_pos;
		}
		if (offset_updated || mouse_updated) {
			pos = to_absolute(mouse_pos);
			m_active_i = index_of(pos);
		}
	}

	Absolute
	GridView::to_absolute(Relative position) const
	{
		return position - m_offset;
	}

	Relative
	GridView::to_relative(Absolute position) const
	{
		return position + m_offset;
	}
}
