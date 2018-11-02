#include "StringUtils.h"

#include "../shading/ShaderManager.h"

namespace prx::utils {
	std::string StringUtils::toString(ShaderType type) {
		switch (type) {
		case ShaderType::FORWARD_RENDERER_DEFAULT: {return std::string("default"); break; }
		default: {return std::string("undefined shader type"); break; }
		}
	}
}