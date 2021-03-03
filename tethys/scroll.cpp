#include "scroll.hpp"

#include "point.hpp"
#include "size.hpp"

namespace tethys {
	Scroll::Scroll(Size screen, Size content, int speed):
		m_min {Point::min(screen - content)},
		m_max {Point::max(screen - content)},
		m_speed {speed},
		m_state {}
	{}

	void
	Scroll::add_x()
	{
		m_state.x += m_speed;
	}

	void
	Scroll::add_y()
	{
		m_state.y += m_speed;
	}

	void
	Scroll::sub_x()
	{
		m_state.x -= m_speed;
	}

	void
	Scroll::sub_y()
	{
		m_state.y -= m_speed;
	}

	void
	Scroll::update(Point& p) const
	{
		p -= m_state;
		p.pick_max(m_min);
		p.pick_min(m_max);
	}
}
