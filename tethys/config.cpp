#include "config.hpp"

#include "exception.hpp"
#include "file.hpp"

#include <string>
#include <unordered_set>

namespace tethys::s {
	struct Pair {
		const std::string key;
		const std::string value;
	};

	const std::string equals = " = ";

	struct BadValue : public Exception {
		const std::string expected;
		BadValue(const std::string a_expected):
			Exception {"Value is not " + a_expected + "."},
			expected {a_expected}
		{}
	};

	struct MissingObjectKey : public Exception {
		const std::string key;
		MissingObjectKey(const std::string a_key):
			Exception {"Missing object key: " + a_key},
			key {a_key}
		{}
	};

	struct NotPair : public Exception {
		NotPair(const std::string line):
			Exception {"Line is not a pair -> " + line}
		{}
	};

	bool
	is_pair(const std::string line)
	{
		auto i = line.find(equals);
		return i != std::string::npos;
	}

	Pair
	parse_pair(const std::string line)
	{
		auto i = line.find(equals);
		if (i == std::string::npos)
			throw NotPair {line};
		return {
			line.substr(0, i),
			line.substr(i + equals.size())
		};
	}

	double
	to_double(const std::string input)
	{
		try {
			return std::stod(input);
		}
		catch (const std::invalid_argument& err) {
			throw BadValue {"a double"};
		}
	}

	double
	pair2double(const Pair pair)
	{
		try {
			return to_double(pair.value);
		}
		catch (const BadValue& err) {
			throw Config::BadValue {pair.key, err.expected};
		}
	}

	Config::Hex
	to_hex(const file::LineList& lines)
	{
		std::unordered_set<std::string> keys = {
			"gold", "industry", "manpower"
		};
		double gold, industry, manpower;
		for (auto const& line : lines) {
			auto pair = parse_pair(line);
			auto got = keys.find(pair.key);
			if (got == keys.end())
				continue;
			keys.erase(got);
			if (pair.key == "gold") {
				gold = pair2double(pair);
			}
			if (pair.key == "industry") {
				industry = pair2double(pair);
			}
			if (pair.key == "manpower") {
				manpower = pair2double(pair);
			}
		}
		if (!keys.empty()) {
			auto first = keys.cbegin();
			throw MissingObjectKey {*first};
		}
		return { gold, industry, manpower };
	}
}

namespace tethys {
	Config::Config(const std::string filename):
		m_lines {file::read_lines(filename)}
	{}

	file::LineList
	Config::find_object_lines(const std::string name) const
	{
		file::LineList lines_found;
		bool object_found = false;
		for (auto const& line : m_lines) {
			if (object_found) {
				if (line.front() != '\t')
					break;
				lines_found.push_back(line.substr(1));
			}
			else if (line == (name + ":")) {
				object_found = true;
			}
		}
		if (object_found)
			return lines_found;
		throw Config::MissingKey {name};
	}

	std::string
	Config::find_value(const std::string key) const
	{
		for (auto const& line : m_lines) {
			if (!s::is_pair(line))
				continue;
			auto pair = s::parse_pair(line);
			if (pair.key == key)
				return pair.value;
		}
		throw Config::MissingKey {key};
	}

	Config::Hex
	Config::get_city_hex() const
	{
		static const std::string name = "city hex";
		return parse_object(name, s::to_hex);
	}

	Config::Hex
	Config::get_forest_hex() const
	{
		static const std::string name = "forest hex";
		return parse_object(name, s::to_hex);
	}

	Config::Hex
	Config::get_mountain_hex() const
	{
		static const std::string name = "mountain hex";
		return parse_object(name, s::to_hex);
	}

	Config::Hex
	Config::get_plains_hex() const
	{
		static const std::string name = "plains hex";
		return parse_object(name, s::to_hex);
	}

	Config::Hex
	Config::get_sea_hex() const
	{
		static const std::string name = "sea hex";
		return parse_object(name, s::to_hex);
	}

	double
	Config::get_gold_per_trade() const
	{
		static const std::string key = "gold per trade";
		return parse_value(key, s::to_double);
	}

	double
	Config::get_trade_value() const
	{
		static const std::string key = "trade value";
		return parse_value(key, s::to_double);
	}

	template<class T>
	T
	Config::parse_object(
		const std::string name,
		T (*parse)(const file::LineList&)
	) const
	{
		try {
			return parse(find_object_lines(name));
		}
		catch (const Config::BadValue& err) {
			throw Config::BadValue {name + " -> " + err.key, err.expected};
		}
		catch (const s::MissingObjectKey& err) {
			throw Config::MissingKey {name + " -> " + err.key};
		}
	}

	template<class T>
	T
	Config::parse_value(
		const std::string key,
		T (*parse)(const std::string)
	) const
	{
		try {
			return parse(find_value(key));
		}
		catch (const s::BadValue& err) {
			throw Config::BadValue {key, err.expected};
		}
	}

	Config::BadValue::BadValue(
		const std::string a_key,
		const std::string a_expected
	):
		Exception {a_key + " is not " + a_expected},
		expected {a_expected},
		key {a_key}
	{}

	Config::MissingKey::MissingKey(const std::string a_key):
		Exception {"Key not found: " + a_key},
		key {a_key}
	{}
}
