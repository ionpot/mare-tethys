#ifndef TETHYS_CFG_FILE_HPP
#define TETHYS_CFG_FILE_HPP

#include "exception.hpp"
#include "file.hpp"

#include <string>

namespace tethys {
	struct CfgFileException : public Exception {
		CfgFileException(std::string text):
			Exception {"CfgFile", text}
		{};
	};

	class CfgFile {
	public:
		class Pair {
		public:
			static const std::string delimiter;
			static bool is_pair(std::string line);
			const std::string section;
			std::string key;
			std::string value;
			Pair(std::string line, std::string section = "");
			double to_double() const;
			int to_int() const;
		private:
			template<class T>
			T to_value(T (*)(std::string)) const;
		};
		class Section {
		public:
			const std::string name;
			Section(std::string name, const file::LineList&);
			Pair find_pair(std::string key) const;
		private:
			file::LineList m_lines;
		};

		CfgFile(std::string filename);

		Pair
		find_pair(std::string key) const;

		Section
		find_section(std::string name) const;

		struct BadValue : public CfgFileException {
			const std::string expected;
			const std::string key;
			const std::string section;
			BadValue(
				std::string key,
				std::string expected,
				std::string section = ""
			);
		};

		struct MissingKey : public CfgFileException {
			const std::string key;
			const std::string section;
			MissingKey(std::string key, std::string section = "");
		};

		struct MissingSection : public CfgFileException {
			const std::string name;
			MissingSection(std::string name);
		};

		struct NotPair : public CfgFileException {
			NotPair(std::string line);
		};

	private:
		const file::LineList m_lines;

		file::LineList
		find_object_lines(std::string name) const;
	};
}

#endif
