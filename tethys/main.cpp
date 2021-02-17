#include "cfg_file.hpp"
#include "config.hpp"
#include "hexagon.hpp"
#include "log.hpp"
#include "point.hpp"
#include "rect.hpp"
#include "rgb.hpp"
#include "sdl.hpp"

#include <tethys/version.hpp>
#include <iostream>
#include <string>

namespace tethys {
	std::string get_title()
	{
		return "Mare Tethys v"
			+ std::to_string(version.major)
			+ "."
			+ std::to_string(version.minor);
	}

	auto create_texture(const sdl::Renderer& renderer, double hex_side)
	{
		Hexagon hex {hex_side};
		auto tx = renderer.create_target_texture(hex.size());
		renderer.set_target(tx);
		renderer.set_color(sdl::RGBA::transparent);
		renderer.clear();
		renderer.set_color(sdl::RGBA::opaque(rgb::red));
		renderer.draw_hex(hex);
		renderer.reset_target();
		return tx;
	}

	class Main {
	public:
		Main(const std::string title, Log& log):
			m_config {CfgFile {"tethys.cfg"}},
			m_sdl {sdl::Context {title, m_config.window_size, log}},
			m_texture {create_texture(m_sdl.renderer, m_config.hex_side)},
			m_tex_pos {100, 100},
			m_put_tex {true}
		{
			log.pair("Hexagon size", m_texture.size);
		}
		void poll()
		{
			auto event = m_sdl.base.poll_event();
			if (event) {
				if (event->is_quit())
					return;
				if (event->is_keydown())
					return;
				check_mouse(*event);
			}
			else {
				render();
				m_sdl.base.delay(1000 / 30);
			}
			poll();
		}
	private:
		Config m_config;
		sdl::Context m_sdl;
		sdl::Texture m_texture;
		Point m_tex_pos;
		bool m_put_tex;
		void check_mouse(sdl::Event& event)
		{
			auto mouse = event.read_mouse_motion();
			if (mouse) {
				Rect rect {m_tex_pos, m_texture.size};
				m_put_tex = !rect.contains(*mouse);
			}
		}
		void render() const
		{
			auto& renderer = m_sdl.renderer;
			renderer.set_color(sdl::RGBA::opaque(rgb::black));
			renderer.clear();
			if (m_put_tex) {
				renderer.put(m_texture, m_tex_pos);
			}
			renderer.present();
		}
	};

	void start(Log&& log)
	{
		auto title = get_title();
		log.put(title);
		log.put("Begin");
		try {
			Main m {title, log};
			log.put("Polling events...");
			m.poll();
		}
		catch (const std::exception& err) {
			log.error(err.what());
		}
		log.put("End");
	}
}

int main(int, char **)
{
	try {
		tethys::start(tethys::Log {"tethys.log"});
	}
	catch (const std::exception& err) {
		std::cerr << err.what() << std::endl;
	}
	return 0;
}
