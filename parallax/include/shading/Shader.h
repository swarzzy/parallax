#pragma once
#ifndef _SHADER_H_
#define _SHADER_H_


#include <vector>
// TODO: get rid of this
#include <optional>
#include <string_view>

#include <GL/glew.h>

#include <hypermath.h>;

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
	};

	class Shader {
	private:
		unsigned int m_ID;
		ShaderSource m_ShaderSource;
		std::vector<Uniform> m_Uniforms;
	
	public:
		Shader(std::string_view vertexPath, std::string_view fragmentPath);
		~Shader();

		inline void bind() const { GLCall(glUseProgram(m_ID)); };
		inline void unbind() const { GLCall(glUseProgram(0)); };

		inline unsigned int getID() const { return m_ID; };
		inline std::vector<Uniform> getUniforms() const { return m_Uniforms; };
		std::optional<int> getUniformLocation(std::string_view uniform) const;

		void setUniform(const std::string& uniformName, hpm::mat4 mat);
		//void setUniform(const std::string& uniformName, hpm::mat3 mat);
		void setUniform(const std::string& uniformName, hpm::vec2 vec);
		void setUniform(const std::string& uniformName, hpm::vec3 vec);
		void setUniform(const std::string& uniformName, hpm::vec4 vec);
		void setUniform(const std::string& uniformName, float floatNum);
		void setUniform(const std::string& uniformName, int intNum);
		void setUniform(const std::string& uniformName, unsigned int uintNum);
		void setUniform(const std::string& uniformName, float* floatArr, unsigned int count);
		void setUniform(const std::string& uniformName, int* floatArr, unsigned int count);
	
	private:
		void loadUniforms();
		void readShaderFromFile(std::string_view vertexPath, std::string_view fragmentPath);
		void compileShader();
	};
}
#endif

