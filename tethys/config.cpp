#include "config.hpp"

#include "cfg_file.hpp"

#include <string>

namespace tethys {
	Config::Hex::Hex(const CfgFile::Section& section):
		gold {section.find_pair("gold").to_double()},
		industry {section.find_pair("industry").to_double()},
		manpower {section.find_pair("manpower").to_double()}
	{}

	Config::Config(const std::string filename):
		m_file {CfgFile {filename}}
	{}

	Config::Hex
	Config::get_city_hex() const
	{
		return Hex {m_file.find_section("city hex")};
	}

	Config::Hex
	Config::get_forest_hex() const
	{
		return Hex {m_file.find_section("forest hex")};
	}

	Config::Hex
	Config::get_mountain_hex() const
	{
		return Hex {m_file.find_section("mountain hex")};
	}

	Config::Hex
	Config::get_plains_hex() const
	{
		return Hex {m_file.find_section("plains hex")};
	}

	Config::Hex
	Config::get_sea_hex() const
	{
		return Hex {m_file.find_section("sea hex")};
	}

	double
	Config::get_gold_per_trade() const
	{
		return m_file.find_pair("gold per trade").to_double();
	}

	double
	Config::get_trade_value() const
	{
		return m_file.find_pair("trade value").to_double();
	}
}
