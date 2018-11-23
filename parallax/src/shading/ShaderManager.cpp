#include "ShaderManager.h"
#include "../utils/SimpleHash.h"

namespace prx {

	static const char* ParallaxDefaultVertexShader = 
#include "sources/ParallaxDefaultVertex.shader"
		;

	static const char* ParallaxDefaultFragmentShader =
#include "sources/ParallaxDefaultFragment.shader"
		;

	static const char* PXDFR_GP_VERTEX_Deafult =
#include "sources/PXDFR_GP_VERTEX.shader"
		;

	static const char* PXDFR_GP_FRAG_Default =
#include "sources/PXDFR_GP_FRAG.shader"
		;

	static const char* PXDFR_LP_VERTEX_Deafult =
#include "sources/PXDFR_LP_VERTEX.shader"
		;

	static const char* PXDFR_LP_FRAG_Default =
#include "sources/PXDFR_LP_FRAG.shader"
		;

	static const char* PXDFR_LP_FRAG_Default_Debug =
#include "sources/PXDFR_LP_FRAG_DEBUG.shader"
		;

	static const char* PXDFR_AP_VERTEX_Deafult =
#include "sources/PXDFR_AP_VERTEX.shader"
		;

	static const char* PXDFR_AP_FRAG_Default =
#include "sources/PXDFR_AP_FRAG.shader"
		;

	unsigned int ShaderManager::m_GlobalShaderCounter = 0;

	ShaderManager::ShaderManager() {}
	
	ShaderManager::~ShaderManager() {
		clear();
	}

	unsigned ShaderManager::loadShader(std::string_view vertexPath, std::string_view fragmentPath) {
		unsigned int id = ++m_GlobalShaderCounter;

		m_Shaders.emplace(id, std::make_shared<Shader>(vertexPath, fragmentPath));
		//m_Shaders.emplace(std::piecewise_construct, std::forward_as_tuple(id),
						  //std::forward_as_tuple(vertexPath, fragmentPath));
		return id;
	}

	unsigned ShaderManager::loadShader(ShaderType shader) {
		unsigned int id = ++m_GlobalShaderCounter;
		switch (shader) {
			case ShaderType::FORWARD_RENDERER_DEFAULT: {
				m_Shaders.emplace(id, std::make_shared<Shader>(ShaderSource(ParallaxDefaultVertexShader, ParallaxDefaultFragmentShader)));
				return id;
			}
			case ShaderType::DEFFERED_RENDERER_GEOMETRY_PASS_DEFAULT: {
				m_Shaders.emplace(id, std::make_shared<Shader>(ShaderSource(PXDFR_GP_VERTEX_Deafult, PXDFR_GP_FRAG_Default)));
				return id;
			}
			case ShaderType::DEFFERED_RENDERER_LIGHTNING_PASS_DEFAULT: {
				m_Shaders.emplace(id, std::make_shared<Shader>(ShaderSource(PXDFR_LP_VERTEX_Deafult, PXDFR_LP_FRAG_Default)));
				return id;
			}
			case ShaderType::DEFFERED_RENDERER_LIGHTNING_PASS_DEFAULT_DBG: {
				m_Shaders.emplace(id, std::make_shared<Shader>(ShaderSource(PXDFR_LP_VERTEX_Deafult, PXDFR_LP_FRAG_Default_Debug)));
				return id;
			}
			case ShaderType::DEFFERED_RENDERER_AMBIENT_PASS_DEFAULT: {
				m_Shaders.emplace(id, std::make_shared<Shader>(ShaderSource(PXDFR_AP_VERTEX_Deafult, PXDFR_AP_FRAG_Default)));
				return id;
			}
			default: {
				PRX_ERROR("SHADER MANAGER: Failed to load shader. Unknown shader type.\n-> TYPE:", shader);
				return 0;
			}
		}
	}

	std::shared_ptr<Shader> ShaderManager::getShader(unsigned int id) {
		auto element = m_Shaders.find(id);
		if (element != m_Shaders.end())
			return element->second;
		PRX_ERROR("SHADER MANAGER: Shader is not loaded yet\n-> SHADDER ID: ", id);
		return nullptr;
	}

	void ShaderManager::deleteUnused() {
		for (auto& shaderPtr : m_Shaders)
			if (shaderPtr.second.use_count() <= 1)
				m_Shaders.erase(shaderPtr.first);
	}

	void ShaderManager::clear() {
		m_Shaders.clear();
	}

}