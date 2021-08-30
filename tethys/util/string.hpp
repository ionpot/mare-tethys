#pragma once

#include <sstream>
#include <string>

namespace tethys::util::string {
	std::string
	from_double(double value)
	{
		std::ostringstream ss;
		ss << value;
		return ss.str();
	}

	template<class T> std::string kv(std::string key, T value);
	template<> std::string kv(std::string key, const char* value);
	template<> std::string kv(std::string key, double value);
	template<> std::string kv(std::string key, std::string value);

	template<class T>
	std::string
	kv(std::string key, T value)
	{
		return kv(key, std::to_string(value));
	}

	template<>
	std::string
	kv(std::string key, const char* value)
	{
		return kv(key, std::string {value});
	}

	template<>
	std::string
	kv(std::string key, double value)
	{
		return kv(key, from_double(value));
	}

	template<>
	std::string
	kv(std::string key, std::string value)
	{
		return key + ": " + value;
	}
}
