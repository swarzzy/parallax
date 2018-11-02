#pragma once
#include "ParallaxException.h"
#include <string>

namespace prx {
	class ImageLoadingException : public ParallaxException {
	public:
		ImageLoadingException(const char* imageFilepath)
			: ParallaxException((std::string("Failed to read image from disk.\n-> PATH: ") + imageFilepath).c_str())
		{}
	};
}
