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
	Scroll::start_down()
	{
		m_state.y = m_speed;
	}

	void
	Scroll::start_left()
	{
		m_state.x = -m_speed;
	}

	void
	Scroll::start_right()
	{
		m_state.x = m_speed;
	}

	void
	Scroll::start_up()
	{
		m_state.y = -m_speed;
	}

	void
	Scroll::stop()
	{
		m_state.clear();
	}

	void
	Scroll::stop_down()
	{
		if (m_state.y > 0)
			m_state.y = 0;
	}

	void
	Scroll::stop_left()
	{
		if (m_state.x < 0)
			m_state.x = 0;
	}

	void
	Scroll::stop_right()
	{
		if (m_state.x > 0)
			m_state.x = 0;
	}

	void
	Scroll::stop_up()
	{
		if (m_state.y < 0)
			m_state.y = 0;
	}

	void
	Scroll::update(Point& p) const
	{
		p -= m_state;
		p.pick_max(m_min);
		p.pick_min(m_max);
	}
}
