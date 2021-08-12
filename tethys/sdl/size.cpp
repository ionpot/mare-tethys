#include "size.hpp"

#include "point.hpp"

#include <string>

namespace tethys::sdl {
	Size::Size(int n):
		width {n}, height {n}
	{}
	Size::Size(const Point& p):
		width {p.x}, height {p.y}
	{}
	Size::Size(int w, int h):
		width {w}, height {h}
	{}

	Size
	Size::operator+(const Size& size) const
	{
		return {width + size.width, height + size.height};
	}

	Size
	Size::operator-(const Size& size) const
	{
		return {width - size.width, height - size.height};
	}

	Size
	Size::operator-(int n) const
	{
		return *this - Size {n};
	}

	Size&
	Size::operator-=(const Size& s)
	{
		*this = *this - s;
		return *this;
	}

	Size&
	Size::operator-=(int n)
	{
		*this = *this - n;
		return *this;
	}

	Point
	Size::to_point() const
	{
		return {width, height};
	}

	std::string
	Size::to_str() const
	{
		return std::to_string(width)
			+ "x"
			+ std::to_string(height);
	}
}
