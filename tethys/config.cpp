#include "config.hpp"

#include "cfg_file.hpp"

namespace tethys {
	Config::Hex::Hex(const CfgFile::Section& section):
		gold {section.find_pair("gold").to_double()},
		industry {section.find_pair("industry").to_double()},
		manpower {section.find_pair("manpower").to_double()}
	{}

	Config::Config(const CfgFile& file):
		city {file.find_section("city hex")},
		forest {file.find_section("forest hex")},
		mountain {file.find_section("mountain hex")},
		plains {file.find_section("plains hex")},
		sea {file.find_section("sea hex")},
		gold_per_trade {file.find_pair("gold per trade").to_double()},
		trade_value {file.find_pair("trade value").to_double()}
	{}
}
