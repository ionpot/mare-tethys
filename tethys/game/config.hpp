#pragma once

#include <util/cfg_file.hpp>

namespace tethys::game {
	struct Config {
		struct Hex {
			double gold;
			double industry;
			double manpower;
			Hex(const util::CfgFile::Section&);
		};

		Hex city;
		Hex forest;
		Hex mountain;
		Hex plains;
		Hex sea;

		double gold_per_trade;
		double trade_value;

		Config(const util::CfgFile&);
	};
}
