#pragma once

#include "point.hpp"

#include <string>

namespace tethys::sdl {
	struct Size {
		int width {0};
		int height {0};

		Size() = default;
		Size(int width_and_height);
		Size(const Point&);
		Size(int width, int height);

		Size operator+(const Size&) const;
		Size operator-(const Size&) const;
		Size operator-(int) const;
		Size& operator-=(const Size&);
		Size& operator-=(int);

		Point to_point() const;

		std::string to_str() const;
	};
}
