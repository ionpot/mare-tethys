#ifndef TETHYS_CFG_FILE_HPP
#define TETHYS_CFG_FILE_HPP

#include "exception.hpp"
#include "file.hpp"

#include <string>

namespace tethys {
	struct CfgFileException : public Exception {
		CfgFileException(const std::string text):
			Exception {"CfgFile", text}
		{};
	};

	class CfgFile {
	public:
		class Pair {
		public:
			static const std::string delimiter;
			static bool is_pair(const std::string line);
			const std::string section;
			std::string key;
			std::string value;
			Pair(const std::string line, const std::string section = "");
			double to_double() const;
		private:
			template<class T>
			T to_value(T (*)(const std::string)) const;
		};
		class Section {
		public:
			const std::string name;
			Section(const std::string name, const file::LineList&);
			Pair find_pair(const std::string key) const;
		private:
			file::LineList m_lines;
		};

		CfgFile(const std::string filename);

		Pair
		find_pair(const std::string key) const;

		Section
		find_section(const std::string name) const;

		struct BadValue : public CfgFileException {
			const std::string expected;
			const std::string key;
			const std::string section;
			BadValue(
				const std::string key,
				const std::string expected,
				const std::string section = ""
			);
		};

		struct MissingKey : public CfgFileException {
			const std::string key;
			const std::string section;
			MissingKey(const std::string key, const std::string section = "");
		};

		struct MissingSection : public CfgFileException {
			const std::string name;
			MissingSection(const std::string name);
		};

		struct NotPair : public CfgFileException {
			NotPair(const std::string line);
		};

	private:
		const file::LineList m_lines;

		file::LineList
		find_object_lines(const std::string name) const;
	};
}

#endif
