#pragma once
#ifndef _PARALLAX_GRAPHICS_SHADING_SHADERMANAGER_H_
#define _PARALLAX_GRAPHICS_SHADING_SHADERMANAGER_H_
#include <map>

#include "Shader.h"

namespace prx {
	
	enum class SHADER_SRC {
		DEFAULT
	};

	class ShaderManager {
	private:
		static std::map<unsigned int, Shader> m_Shaders;
		
	public:
		ShaderManager() = delete;

		static unsigned int loadShader(std::string_view name, 
									   std::string_view vertexPath, 
									   std::string_view fragmentPath);

		static unsigned int loadShader(std::string_view name, SHADER_SRC shader);

		static Shader* getShader(std::string_view name);
		static Shader* getShader(unsigned int id);

		static void deleteShader(std::string_view name);
		static void deleteShader(unsigned int id);
		
		static void clear();
	};
}
#endif