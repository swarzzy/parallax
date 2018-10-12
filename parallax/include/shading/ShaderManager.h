#pragma once
#ifndef _PARALLAX_GRAPHICS_SHADING_SHADERMANAGER_H_
#define _PARALLAX_GRAPHICS_SHADING_SHADERMANAGER_H_
#include <map>

#include "Shader.h"

namespace prx {
	
	enum class ShaderType {
		DEFAULT
	};

	class ShaderManager {
	private:
		static unsigned int m_GlobalShaderCounter;
		
		static std::map<unsigned int, Shader> m_Shaders;
		
	public:
		ShaderManager() = delete;

		static unsigned int loadShader(std::string_view vertexPath, std::string_view fragmentPath);

		static unsigned int loadShader(ShaderType shader);

		static Shader* getShader(unsigned int id);

		static void deleteShader(unsigned int id);
		
		static void clear();
	};
}
#endif