#ifndef TETHYS_SIZE_HPP
#define TETHYS_SIZE_HPP

namespace tethys {
	struct Size {
		int width = 0;
		int height = 0;
		Size operator+(const Size& size)
		{
			return {width + size.width, height + size.height};
		}
		Size operator-(const Size& size)
		{
			return {width - size.width, height - size.height};
		}
	};
}

#endif
