#pragma once

#include "value.hpp"

#include <string>

namespace tethys::game {
	class Bonus : public Value {
	public:
		std::string to_string() const
		{
			auto str = Value::to_string();
			return is_positive() ? "+" + str : str;
		}
	};
}
