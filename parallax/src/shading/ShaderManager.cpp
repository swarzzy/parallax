#include "ShaderManager.h"
#include "../utils/SimpleHash.h"

namespace prx {

	static const char* ParallaxDefaultVertexShader = 
#include "sources/ParallaxDefaultVertex.shader"
		;

	static const char* ParallaxDefaultFragmentShader =
#include "sources/ParallaxDefaultFragment.shader"
		;

	unsigned int ShaderManager::m_GlobalShaderCounter = 0;

	
	std::map<unsigned int, Shader> ShaderManager::m_Shaders = std::map<unsigned int, Shader>();

	unsigned ShaderManager::loadShader(std::string_view vertexPath, std::string_view fragmentPath) {
		unsigned int id = ++m_GlobalShaderCounter;
		
		m_Shaders.emplace(std::piecewise_construct, std::forward_as_tuple(id),
						  std::forward_as_tuple(vertexPath, fragmentPath));
		return id;
	}

	unsigned ShaderManager::loadShader(ShaderType shader) {
		if (shader == ShaderType::FORWARD_RENDERER_DEFAULT) {
			unsigned int id = ++m_GlobalShaderCounter;

			m_Shaders.emplace(std::piecewise_construct, std::forward_as_tuple(id),
				std::forward_as_tuple(ShaderSource(ParallaxDefaultVertexShader, ParallaxDefaultFragmentShader)));
			return id;
		}
		else {
			PRX_ERROR("Shader Manager: Failed to load shader. Unknown shader type: ", shader);
			return 0;
		}
	}

	Shader* ShaderManager::getShader(unsigned int id) {
		auto element = m_Shaders.find(id);
		if (element != m_Shaders.end())
			return &(element->second);
		PRX_ERROR("(Shader Manager): Shader (ID: ", id, ") is not loaded yet");
		return nullptr;
	}

	void ShaderManager::deleteShader(unsigned id) {
		m_Shaders.erase(id);
	}

	void ShaderManager::clear() {
		m_Shaders.clear();
	}

}
