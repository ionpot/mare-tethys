#ifndef TETHYS_SCROLL_HPP
#define TETHYS_SCROLL_HPP

#include <sdl/point.hpp>
#include <sdl/size.hpp>

namespace tethys {
	class Scroll {
	public:
		Scroll(Size screen, Size content, int speed);
		void start_left();
		void start_right();
		void start_up();
		void start_down();
		void stop();
		void stop_left();
		void stop_right();
		void stop_up();
		void stop_down();
		void update(Point&) const;
	private:
		const Point m_min;
		const Point m_max;
		const int m_speed;
		Point m_state;
	};
}

#endif
