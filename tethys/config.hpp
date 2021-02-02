#ifndef TETHYS_CONFIG_HPP
#define TETHYS_CONFIG_HPP

#include "cfg_file.hpp"

#include <string>

namespace tethys {
	class Config {
	public:
		Config(const std::string filename);

		struct Hex {
			double gold;
			double industry;
			double manpower;
			Hex(const CfgFile::Section& lines);
		};
		Hex get_city_hex() const;
		Hex get_forest_hex() const;
		Hex get_mountain_hex() const;
		Hex get_plains_hex() const;
		Hex get_sea_hex() const;

		double get_gold_per_trade() const;
		double get_trade_value() const;

	private:
		const CfgFile m_file;
	};
}

#endif
