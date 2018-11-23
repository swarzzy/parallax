#pragma once
#ifndef _PARALLAX_GRAPHICS_SHADING_SHADERMANAGER_H_
#define _PARALLAX_GRAPHICS_SHADING_SHADERMANAGER_H_
#include <map>

#include "Shader.h"
#include "../utils/Singleton.h"

namespace prx {
	
	enum class ShaderType {
		FORWARD_RENDERER_DEFAULT,
		DEFFERED_RENDERER_GEOMETRY_PASS_DEFAULT,
		DEFFERED_RENDERER_LIGHTNING_PASS_DEFAULT,
		DEFFERED_RENDERER_LIGHTNING_PASS_DEFAULT_DBG,
		DEFFERED_RENDERER_AMBIENT_PASS_DEFAULT
	};

	class ShaderManager final : public Singleton<ShaderManager> {
		PRX_DISALLOW_COPY_AND_MOVE(ShaderManager)
	public:
		friend class Singleton<ShaderManager>;
	private:
		static unsigned int m_GlobalShaderCounter;
		
		std::map<unsigned int, std::shared_ptr<Shader>> m_Shaders;
		
	public:
		ShaderManager();
		~ShaderManager();

		unsigned int loadShader(std::string_view vertexPath, std::string_view fragmentPath);

		unsigned int loadShader(ShaderType shader);

		std::shared_ptr<Shader> getShader(unsigned int id);

		void deleteUnused();
		
		void clear();
	};
}
#endif