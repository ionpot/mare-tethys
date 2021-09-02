#pragma once

#include "value.hpp"

#include <util/cfg_file.hpp>

namespace tethys::game {
	struct Config {
		struct Hex {
			Value gold;
			Value industry;
			Value manpower;
			Hex(const util::CfgFile::Section&);
		};

		Hex city;
		Hex forest;
		Hex mountain;
		Hex plains;
		Hex sea;

		Value gold_per_trade;
		Value trade_value;

		Config(const util::CfgFile&);
	};
}
