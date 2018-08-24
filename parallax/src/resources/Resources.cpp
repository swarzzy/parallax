#include "Resources.h"
#include "../utils/SimpleHash.h"

namespace prx {

	std::map<unsigned int, prx::Shader> Resources::m_Shaders = std::map<unsigned int, prx::Shader>();

	prx::Shader* Resources::loadShader(std::string_view name, const std::string & vertexPath, const std::string & fragmentPath) {
		unsigned int id = prx::SimpleHash::hashString(name);
		auto element = m_Shaders.find(id);
		if (element != m_Shaders.end())
			return &element->second;

		auto result = m_Shaders.emplace(std::piecewise_construct, std::forward_as_tuple(id),
			std::forward_as_tuple(vertexPath, fragmentPath));
		return &result.first->second;
	}

	prx::Shader* Resources::getShader(std::string_view name) {
		auto element = m_Shaders.find(prx::SimpleHash::hashString(name));
		if (element != m_Shaders.end())
			return &element->second;
		prx::Log::message("Resources: requested shader object does not exist", prx::LOG_WARNING);
		return nullptr;
	}

	Shader* Resources::getShader(unsigned hashName) {
		auto element = m_Shaders.find(hashName);
		if (element != m_Shaders.end())
			return &element->second;
		prx::Log::message("Resources: requested shaer object does not exist", prx::LOG_WARNING);
		return nullptr;
	}

	void Resources::deleteShader(std::string_view name) {
		m_Shaders.erase(prx::SimpleHash::hashString(name));
	}

	void Resources::deleteShader(unsigned hashName) {
		m_Shaders.erase(hashName);
	}
}

