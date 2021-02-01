#ifndef TETHYS_CONFIG_HPP
#define TETHYS_CONFIG_HPP

#include "exception.hpp"
#include "file.hpp"

#include <string>

namespace tethys {
	class Config {
	public:
		Config(const std::string filename);

		struct Hex {
			const double gold;
			const double industry;
			const double manpower;
		};
		Hex get_city_hex() const;
		Hex get_forest_hex() const;
		Hex get_mountain_hex() const;
		Hex get_plains_hex() const;
		Hex get_sea_hex() const;

		double get_gold_per_trade() const;
		double get_trade_value() const;

		struct BadValue : public Exception {
			const std::string expected;
			const std::string key;
			BadValue(const std::string key, const std::string expected);
		};

		struct MissingKey : public Exception {
			const std::string key;
			MissingKey(const std::string key);
		};

	private:
		const file::LineList m_lines;

		file::LineList
		find_object_lines(const std::string name) const;

		std::string
		find_value(const std::string key) const;

		template<class T>
		T parse_object(
			const std::string name,
			T (*parse)(const file::LineList&)
		) const;

		template<class T>
		T parse_value(
			const std::string key,
			T (*parse)(const std::string)
		) const;
	};
}

#endif
