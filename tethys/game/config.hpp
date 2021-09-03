#pragma once

#include "bonus.hpp"
#include "value.hpp"

#include <util/cfg_file.hpp>

namespace tethys::game {
	struct Config {
		struct Hex {
			Bonus gold;
			Bonus industry;
			Bonus manpower;
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
