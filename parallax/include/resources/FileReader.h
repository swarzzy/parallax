#pragma once
#ifndef _FILEREADER_H_
#define _FILEREADER_H_

#include <string_view> 
// TODO: Get rid of this
#include <optional>

namespace prx {

	class FileReader {
	private:
		FileReader();
	public:
		// TODO: Make proper error handling
		static std::optional<std::string> readTextFile(std::string_view path);
	};
}

#endif