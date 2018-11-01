#pragma once
#include "ParallaxException.h"
#include <string>

namespace prx {
	class UninitializedResourceUsedException : public ParallaxException {
	public:
		UninitializedResourceUsedException(const char* resourceFilepath)
			: ParallaxException((std::string("Trying to use uninitialized resource.\n-> PATH: ") + resourceFilepath).c_str())
		{}
	};
}