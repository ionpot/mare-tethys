#ifndef TETHYS_SCROLL_HPP
#define TETHYS_SCROLL_HPP

#include "point.hpp"
#include "size.hpp"

namespace tethys {
	class Scroll {
	public:
		Scroll(Size screen, Size content, int speed);
		void add_x();
		void add_y();
		void sub_x();
		void sub_y();
		void update(Point&) const;
	private:
		const Point m_min;
		const Point m_max;
		const int m_speed;
		Point m_state;
	};
}

#endif
