#ifndef TETHYS_SCREEN_HPP
#define TETHYS_SCREEN_HPP

#include "config.hpp"
#include "log.hpp"
#include "point.hpp"
#include "sdl.hpp"

namespace tethys {
	class Screen {
	public:
		enum class Status { ok, quit };
		Screen(const Config&, const sdl::Renderer&, Log&);
		Status handle(sdl::Event&);
		void render(const sdl::Renderer&) const;
	private:
		sdl::Texture m_texture;
		Point m_tex_pos;
		bool m_put_tex;
	};
}

#endif
