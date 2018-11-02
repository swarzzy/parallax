#pragma once
#ifndef _FILEREADER_H_
#define _FILEREADER_H_

#include <optional>
#include "../utils/error/FileReadException.h"

namespace prx {

	// TODO: Get rid of this stuff
	class FileReader {
	private:
		FileReader();
	public:
		// TODO: Make proper error handling
		static std::optional<std::string> readTextFile(std::string_view path);
	};

	inline std::string read_file_as_text(std::string_view path) {
		auto result = prx::FileReader::readTextFile(path);
		if (!result)
			throw FileReadException("path");
		return result.value();
	}
}
#endif