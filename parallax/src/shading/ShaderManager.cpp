#include <shading/ShaderManager.h>
#include "utils/SimpleHash.h"

namespace prx {

	static const char* ParallaxDefaultVertexShader = 
#include "sources/ParallaxDefaultVertex.shader"
		;

	static const char* ParallaxDefaultFragmentShader =
#include "sources/ParallaxDefaultFragment.shader"
		;

	std::map<unsigned int, Shader> ShaderManager::m_Shaders = std::map<unsigned int, Shader>();

	unsigned ShaderManager::loadShader(std::string_view name, 
									   std::string_view vertexPath,
									   std::string_view fragmentPath) {
		unsigned int id = SimpleHash::hashString(name);
		auto element = m_Shaders.find(id);
		if (element != m_Shaders.end()) {
			PRX_WARN("(Shader Manager): Shader: ", name, " already loaded.");
			return id;
		}
		m_Shaders.emplace(std::piecewise_construct, std::forward_as_tuple(id),
						  std::forward_as_tuple(vertexPath, fragmentPath));
		return id;
	}

	unsigned ShaderManager::loadShader(std::string_view name, SHADER_SRC shader) {
		if (shader == SHADER_SRC::DEFAULT) {
			unsigned int id = SimpleHash::hashString(name);
			auto element = m_Shaders.find(id);
			if (element != m_Shaders.end()) {
				PRX_WARN("(Shader Manager): Shader: ", name, " already loaded.");
				return id;
			}
			m_Shaders.emplace(std::piecewise_construct, std::forward_as_tuple(id),
				std::forward_as_tuple(ShaderSource(ParallaxDefaultVertexShader, ParallaxDefaultFragmentShader)));
			return id;
		}
	}

	Shader* ShaderManager::getShader(std::string_view name) {
		auto element = m_Shaders.find(SimpleHash::hashString(name));
		if (element != m_Shaders.end())
			return &element->second;
		PRX_ERROR("(Shader Manager): Shader: ", name, " is not loaded yet.");
		return nullptr;
	}

	Shader* ShaderManager::getShader(unsigned int id) {
		auto element = m_Shaders.find(id);
		if (element != m_Shaders.end())
			return &(element->second);
		PRX_ERROR("(Shader Manager): Shader (id: ", id, ") is not loaded yet");
		return nullptr;
	}

	void ShaderManager::deleteShader(std::string_view name) {
		m_Shaders.erase(SimpleHash::hashString(name));
	}

	void ShaderManager::deleteShader(unsigned id) {
		m_Shaders.erase(id);
	}

	void ShaderManager::clear() {
		m_Shaders.clear();
	}

}
