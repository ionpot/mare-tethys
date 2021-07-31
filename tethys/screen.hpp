#pragma once

#include "config.hpp"
#include "grid_view.hpp"

#include <sdl/context.hpp>
#include <sdl/event.hpp>
#include <sdl/point.hpp>
#include <sdl/renderer.hpp>
#include <util/log.hpp>

namespace tethys {
	class Screen {
	public:
		enum class Status { ok, quit };
		Screen(const Config&, const sdl::Context&, util::Log&);
		Status handle(const sdl::Event&);
		void render(const sdl::Renderer&) const;
		void update();
	private:
		bool m_focus;
		GridView m_grid_view;
		sdl::Point m_mouse_pos;
		Status handle_key(const sdl::KeyEvent&);
	};
}
