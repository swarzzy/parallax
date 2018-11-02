#pragma once
#include "ParallaxException.h"
#include <string>

namespace prx {
	class FileReadException : public ParallaxException {
	public:
		FileReadException(const char* imageFilepath)
			: ParallaxException((std::string("Failed to read file from disk.\n-> PATH: ") + imageFilepath).c_str())
		{}
	};
}
