#ifndef TETHYS_CONFIG_HPP
#define TETHYS_CONFIG_HPP

#include <sdl/size.hpp>
#include <util/cfg_file.hpp>

namespace tethys {
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

		double hex_side;

		sdl::Size window_size;

		Config(const util::CfgFile&);
	};
}

#endif
