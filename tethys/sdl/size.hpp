#pragma once

#include "point.hpp"

#include <string>

namespace tethys::sdl {
	struct Size {
		int width {0};
		int height {0};

		Size() = default;
		Size(int n):
			width {n}, height {n}
		{}
		Size(const Point& p):
			width {p.x}, height {p.y}
		{}
		Size(int w, int h):
			width {w}, height {h}
		{}

		Size operator+(const Size& size) const
		{
			return {width + size.width, height + size.height};
		}
		Size operator-(const Size& size) const
		{
			return {width - size.width, height - size.height};
		}
		Size operator-(int n) const
		{
			return *this - Size {n};
		}
		Size& operator-=(const Size& s)
		{
			*this = *this - s;
			return *this;
		}
		Size& operator-=(int n)
		{
			*this = *this - n;
			return *this;
		}

		Point to_point() const
		{
			return {width, height};
		}

		std::string to_str() const
		{
			return std::to_string(width)
				+ "x"
				+ std::to_string(height);
		}
	};
}
