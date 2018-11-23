#pragma once
#ifndef _SHADER_H_
#define _SHADER_H_


#include <vector>
#include <optional>
#include <string_view>

#include "../ext/GL/glew.h"

#include <hypermath.h>

#include "../utils/error_handling/GLErrorHandler.h"

namespace prx {
	struct Uniform {
		std::string		name;
		int				location;
		unsigned int	type;
		int				size;
	};

	struct ShaderSource {
		std::string vertexSource;
		std::string fragmentSource;

		ShaderSource() {};
		ShaderSource(const char* _vertexSource, const char* _fragmentSource)
			: vertexSource(_vertexSource), fragmentSource(_fragmentSource) {}
	};

	class Shader {
	private:
		unsigned int		 m_ID;
		ShaderSource		 m_ShaderSource;
		std::vector<Uniform> m_Uniforms;
	
	public:
		Shader(std::string_view vertexPath, std::string_view fragmentPath);
		Shader(const ShaderSource& source);
		~Shader();

		inline void bind()   const { GLCall(glUseProgram(m_ID)); };
		inline void unbind() const { GLCall(glUseProgram(0));    };

		inline unsigned int getID() const { return m_ID; };
		inline std::vector<Uniform> getUniforms() const { return m_Uniforms; };
		std::optional<int> getUniformLocation(std::string_view uniform) const;

		void setUniform(std::string_view uniformName, hpm::mat4 mat);
		void setUniform(std::string_view uniformName, hpm::vec2 vec);
		void setUniform(std::string_view uniformName, hpm::vec3 vec);
		void setUniform(std::string_view uniformName, hpm::vec4 vec);
		void setUniform(std::string_view uniformName, float floatNum);
		void setUniform(std::string_view uniformName, int intNum);
		void setUniform(std::string_view uniformName, unsigned int uintNum);
		void setUniform(std::string_view uniformName, float* floatArr, unsigned int count);
		void setUniform(std::string_view uniformName, hpm::vec3* vec3Arr, unsigned int count);
		void setUniform(std::string_view uniformName, int* floatArr, unsigned int count);
		//void setUniform(const std::string& uniformName, hpm::mat3 mat);
	
	private:
		void loadUniforms();
		void readShaderFromFile(std::string_view vertexPath, std::string_view fragmentPath);
		void compileShader();
	};
}
#endif

