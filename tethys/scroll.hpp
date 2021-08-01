#pragma once

#include <sdl/point.hpp>
#include <sdl/size.hpp>

#include <string>

namespace tethys {
	class Scroll {
	public:
		Scroll(sdl::Size screen, sdl::Size content, int speed);
		sdl::Point next(sdl::Point) const;
		void start_left();
		void start_right();
		void start_up();
		void start_down();
		void stop();
		void stop_left();
		void stop_right();
		void stop_up();
		void stop_down();
		std::string to_str() const;

	private:
		const sdl::Point m_min;
		const sdl::Point m_max;
		const int m_speed;
		sdl::Point m_state;
	};
}
