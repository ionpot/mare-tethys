#include "config.hpp"

#include "file.hpp"

#include <stdexcept>
#include <string>

namespace tethys::s {
	struct BadValue : public CfgFileException {
		const std::string expected;
		BadValue(const std::string expected):
			CfgFileException {"Value is not " + expected + "."},
			expected {expected}
		{}
	};

	std::string
	key_str(const std::string key, const std::string section)
	{
		if (section.empty())
			return key;
		return section + " -> " + key;
	}

	double
	to_double(const std::string input)
	{
		try {
			return std::stod(input);
		}
		catch (const std::invalid_argument&) {
			throw BadValue {"a double"};
		}
	}

	int
	to_int(const std::string input)
	{
		try {
			return std::stoi(input);
		}
		catch (const std::invalid_argument&) {
			throw BadValue {"an integer"};
		}
	}
}

namespace tethys {
	const std::string
	CfgFile::Pair::delimiter = " = ";

	bool
	CfgFile::Pair::is_pair(const std::string line)
	{
		auto i = line.find(delimiter);
		return i != std::string::npos;
	}

	CfgFile::Pair::Pair(const std::string line, const std::string section):
		section {section}
	{
		auto i = line.find(delimiter);
		if (i == std::string::npos)
			throw NotPair {line};
		key = line.substr(0, i);
		value = line.substr(i + delimiter.size());
	}

	double
	CfgFile::Pair::to_double() const
	{
		return to_value(s::to_double);
	}

	int
	CfgFile::Pair::to_int() const
	{
		return to_value(s::to_int);
	}

	template<class T>
	T
	CfgFile::Pair::to_value(
		T (*parse)(const std::string)
	) const
	{
		try {
			return parse(value);
		}
		catch (const s::BadValue& err) {
			throw BadValue {key, err.expected, section};
		}
	}

	CfgFile::Section::Section(
		const std::string name,
		const file::LineList& lines
	):
		name {name}
	{
		bool section_found {false};
		for (auto const& line : lines) {
			if (section_found) {
				if (line.front() != '\t')
					break;
				m_lines.push_back(line.substr(1));
			}
			else if (line == (name + ":")) {
				section_found = true;
			}
		}
		if (!section_found)
			throw MissingSection {name};
	}

	CfgFile::Pair
	CfgFile::Section::find_pair(const std::string key) const
	{
		for (auto const& line : m_lines) {
			if (Pair::is_pair(line)) {
				Pair pair {line, name};
				if (pair.key == key)
					return pair;
			}
		}
		throw MissingKey {key, name};
	}

	CfgFile::CfgFile(const std::string filename):
		m_lines {file::read_lines(filename)}
	{}

	CfgFile::Pair
	CfgFile::find_pair(const std::string key) const
	{
		for (auto const& line : m_lines) {
			if (!Pair::is_pair(line))
				continue;
			Pair pair {line};
			if (pair.key == key)
				return pair;
		}
		throw MissingKey {key};
	}

	CfgFile::Section
	CfgFile::find_section(const std::string name) const
	{
		return Section {name, m_lines};
	}

	CfgFile::BadValue::BadValue(
		const std::string key,
		const std::string expected,
		const std::string section
	):
		CfgFileException {s::key_str(key, section) + " is not " + expected + "."},
		expected {expected},
		key {key},
		section {section}
	{}

	CfgFile::MissingKey::MissingKey(
		const std::string key,
		const std::string section
	):
		CfgFileException {"Key not found: " + s::key_str(key, section)},
		key {key},
		section {section}
	{}

	CfgFile::MissingSection::MissingSection(const std::string name):
		CfgFileException {"Missing section: " + name},
		name {name}
	{}

	CfgFile::NotPair::NotPair(const std::string line):
		CfgFileException {"Line is not a pair -> " + line}
	{}
}
