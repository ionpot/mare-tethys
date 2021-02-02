#ifndef TETHYS_CONFIG_HPP
#define TETHYS_CONFIG_HPP

#include "cfg_file.hpp"

namespace tethys {
	struct Config {
		struct Hex {
			double gold;
			double industry;
			double manpower;
			Hex(const CfgFile::Section&);
		};
		Hex city;
		Hex forest;
		Hex mountain;
		Hex plains;
		Hex sea;

		double gold_per_trade;
		double trade_value;

		Config(const CfgFile&);
	};
}

#endif
