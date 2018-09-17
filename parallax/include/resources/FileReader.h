#pragma once
#ifndef _FILEREADER_H_
#define _FILEREADER_H_

#include <string_view> 
#include <optional>

namespace prx {

	class FileReader {
	private:
		FileReader();
	public:
		static std::optional<std::string> readTextFile(std::string_view path);
	};
}

#endif