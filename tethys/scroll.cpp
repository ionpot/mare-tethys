#include "scroll.hpp"

#include <sdl/point.hpp>
#include <sdl/size.hpp>

#include <string>

namespace tethys {
	Scroll::Scroll(sdl::Size screen, sdl::Size content, int speed):
		m_min {sdl::Point::min(screen - content)},
		m_max {sdl::Point::max(screen - content)},
		m_speed {speed},
		m_state {}
	{}

	sdl::Point
	Scroll::next(sdl::Point p) const
	{
		sdl::Point b {p - m_state};
		b.pick_max(m_min);
		b.pick_min(m_max);
		return b;
	}

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

	std::string
	Scroll::to_str() const
	{
		return "min " + m_min.to_str() + ", max " + m_max.to_str();
	}
}
