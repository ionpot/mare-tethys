#ifndef TETHYS_RGB_HPP
#define TETHYS_RGB_HPP

namespace tethys {
	struct RGB {
		int red;
		int green;
		int blue;
	};
	namespace rgb {
		const RGB black {0, 0, 0};
		const RGB dark_blue {50, 50, 150};
		const RGB red {255, 0, 0};
	}
}

#endif
