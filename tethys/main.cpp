#include "cfg_file.hpp"
#include "config.hpp"
#include "log.hpp"
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

	auto create_texture(const sdl::Renderer& renderer)
	{
		auto tx = renderer.create_target_texture({100, 100});
		renderer.set_target(tx);
		renderer.set_color(sdl::RGBA::transparent);
		renderer.clear();
		renderer.set_color(sdl::RGBA::opaque(rgb::red));
		renderer.draw_line({{0, 0}, {100, 100}});
		renderer.reset_target();
		return tx;
	}

	class Main {
	public:
		Main(const std::string title, Log& log):
			m_config {CfgFile {"tethys.cfg"}},
			m_sdl {sdl::Context {title, {640, 480}, log}},
			m_texture {create_texture(m_sdl.renderer)}
		{}
		void poll()
		{
			auto event = m_sdl.base.poll_event();
			if (event) {
				if (event->is_quit())
					return;
				if (event->is_keydown())
					return;
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
		void render() const
		{
			auto& renderer = m_sdl.renderer;
			renderer.set_color(sdl::RGBA::opaque(rgb::dark_blue));
			renderer.clear();
			renderer.put(m_texture, {100, 100});
			renderer.present();
		}
	};

	void start(Log&& log)
	{
		auto title = get_title();
		log.put(title);
		try {
			log.put("Begin");
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
