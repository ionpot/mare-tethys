#include "hex_grid.hpp"

#include <game/grid.hpp>
#include <game/hex_type.hpp>

#include <sdl/context.hpp>
#include <sdl/event.hpp>
#include <sdl/hexagon.hpp>
#include <sdl/key.hpp>
#include <sdl/point.hpp>
#include <sdl/renderer.hpp>
#include <sdl/size.hpp>

#include <util/grid.hpp>
#include <util/log.hpp>

#include <optional>
#include <utility> // std::move

namespace tethys::ui {
	HexGrid::HexGrid(
			game::Grid&& game_grid,
			sdl::Hexagon hex,
			sdl::Size view_size,
			int scroll_speed,
			const sdl::Context& sdl,
			util::Log& log
	):
		m_game_grid {std::move(game_grid)},
		m_hex_grid {hex},
		m_max_visible {m_hex_grid.max_visible(view_size)},
		m_visible_section {m_game_grid.clamp(m_max_visible)},
		m_active_i {},
		m_mouse_pos {},
		m_offset {},
		m_scroll {
			view_size,
			m_hex_grid.size_of(m_game_grid.size()),
			scroll_speed
		},
		m_textures {hex, sdl}
	{
		log.pair("Hex size", hex.size().to_str());
		log.pair("Grid size",
			m_game_grid.size().to_str()
			+ " (" + m_hex_grid.size_of(m_game_grid.size()).to_str() + ")"
		);
		log.pair("Max visible size", m_max_visible.to_str());
		log.pair("Scroll", m_scroll.to_str());
	}

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
		return m_game_grid.begin(m_visible_section);
	}

	std::optional<util::GridIndex>
	HexGrid::find_active_index(sdl::Point mouse_pos) const
	{
		auto pos = m_offset + mouse_pos;
		if (m_active_i) {
			if (m_hex_grid.contains(pos, *m_active_i))
				return m_active_i;
		}
		for (auto iter = begin(); iter.valid(); iter.next()) {
			auto i = iter.index();
			if (m_hex_grid.contains(pos, i)) {
				return i;
			}
		}
		return {};
	}

	util::GridSection
	HexGrid::get_visible_section(sdl::Point offset) const
	{
		auto start = m_hex_grid.get_visible_index(offset);
		util::GridSection section {m_max_visible, start};
		return m_game_grid.clamp(section);
	}

	void
	HexGrid::on_focus_lost()
	{
		m_scroll.stop();
	}

	void
	HexGrid::on_key(const sdl::KeyEvent& event)
	{
		switch (event.key) {
		case sdl::Key::left:
			if (event.pressed)
				m_scroll.start_left();
			else
				m_scroll.stop_left();
			break;
		case sdl::Key::right:
			if (event.pressed)
				m_scroll.start_right();
			else
				m_scroll.stop_right();
			break;
		case sdl::Key::up:
			if (event.pressed)
				m_scroll.start_up();
			else
				m_scroll.stop_up();
			break;
		case sdl::Key::down:
			if (event.pressed)
				m_scroll.start_down();
			else
				m_scroll.stop_down();
			break;
		default:
			break;
		}
	}

	sdl::Point
	HexGrid::position_of(util::GridIndex i) const
	{
		return m_hex_grid.position_of(i) - m_offset;
	}

	void
	HexGrid::render(const sdl::Renderer& rdr) const
	{
		for (auto iter = begin(); iter.valid(); iter.next()) {
			auto type = m_game_grid.cell(iter);
			if (auto base = m_textures.base_of(type)) {
				rdr.put(*base, position_of(iter.index()));
			}
		}
		if (m_active_i) {
			auto i = *m_active_i;
			auto type = m_game_grid.cell(i);
			if (auto base = m_textures.base_of(type)) {
				rdr.put(m_textures.active, position_of(i));
			}
		}
		for (auto iter = begin(); iter.valid(); iter.next()) {
			auto type = m_game_grid.cell(iter);
			if (auto overlay = m_textures.overlay_of(type)) {
				auto pos = position_of(iter.index());
				rdr.put(overlay->texture, pos + overlay->offset);
			}
		}
	}

	void
	HexGrid::update(sdl::Point mouse_pos)
	{
		auto offset = m_scroll.next(m_offset);
		auto offset_updated = offset != m_offset;
		if (offset_updated) {
			m_visible_section = get_visible_section(offset);
			m_offset = offset;
		}
		auto mouse_updated = mouse_pos != m_mouse_pos;
		if (mouse_updated) {
			m_mouse_pos = mouse_pos;
		}
		if (offset_updated || mouse_updated) {
			m_active_i = find_active_index(mouse_pos);
		}
	}
}
