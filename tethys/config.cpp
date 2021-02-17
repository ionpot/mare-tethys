#include "config.hpp"

#include "cfg_file.hpp"

namespace tethys {
	Size find_window_size(const CfgFile& file)
	{
		auto section = file.find_section("window");
		return {
			section.find_pair("width").to_int(),
			section.find_pair("height").to_int()
		};
	}

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
		trade_value {file.find_pair("trade value").to_double()},
		hex_side {file.find_pair("hex side").to_double()},
		window_size {find_window_size(file)}
	{}
}
