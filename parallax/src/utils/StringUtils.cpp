#include <utils/StringUtils.h>

#include <shading/ShaderManager.h>

namespace prx::utils {
	std::string StringUtils::toString(ShaderType type) {
		switch (type) {
		case ShaderType::DEFAULT: {return std::string("default"); break; }
		default: {return std::string("undefined shader type"); break; }
		}
	}
}