#include <shading/Shader.h>

#include <optional>
#include <string>

#include <resources/FileReader.h>
#include <utils/log/Log.h>

namespace prx {

	Shader::Shader(std::string_view vertexPath, std::string_view fragmentPath) {

		readShaderFromFile(vertexPath, fragmentPath);

		compileShader();

		loadUniforms();

	}

	Shader::~Shader() {
		glDeleteProgram(m_ID);
	}

	void Shader::readShaderFromFile(std::string_view vertexPath, std::string_view fragmentPath) {

		std::optional<std::string> vertSrc = prx::FileReader::readTextFile(vertexPath);
		std::optional<std::string> fragSrc = prx::FileReader::readTextFile(fragmentPath);
		if (vertSrc)
			m_ShaderSource.vertexSource = vertSrc.value();
		else {
			prx::Log::message("Can not read vertex shader source", prx::LOG_ERROR);
			// TODO: exceptions
			ASSERT(false);
		}
		if (fragSrc)
			m_ShaderSource.fragmentSource = fragSrc.value();
		else {
			prx::Log::message("Can not read fragment shader source", prx::LOG_ERROR);
			// TODO: exceptions
			ASSERT(false);
		}
	}

	void Shader::compileShader() {

		const char* vShaderCode = m_ShaderSource.vertexSource.c_str();
		const char* fShaderCode = m_ShaderSource.fragmentSource.c_str();

		int result;
		unsigned int vertexShader;
		GLCall(vertexShader = glCreateShader(GL_VERTEX_SHADER));
		GLCall(glShaderSource(vertexShader, 1, &vShaderCode, nullptr));
		GLCall(glCompileShader(vertexShader));
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			int length;
			GLCall(glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &length));
			char* message = (char*)alloca(length * sizeof(char));
			GLCall(glGetShaderInfoLog(vertexShader, length, &length, message));
			std::string out = "Failed to compile vertex shader: " + std::string(message);
			prx::Log::message(out, prx::LOG_WARNING);
			//ASSERT(false);
		}

		unsigned int fragmentShader;
		GLCall(fragmentShader = glCreateShader(GL_FRAGMENT_SHADER));
		GLCall(glShaderSource(fragmentShader, 1, &fShaderCode, nullptr));
		GLCall(glCompileShader(fragmentShader));
		GLCall(glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);)
			if (result == GL_FALSE) {
				int length;
				GLCall(glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &length));
				char* message = (char*)alloca(length * sizeof(char));
				GLCall(glGetShaderInfoLog(fragmentShader, length, &length, message));
				std::string out = "Failed to compile fragment shader: " + std::string(message);
				prx::Log::message(out, prx::LOG_WARNING);
				//ASSERT(false);
			}

		GLCall(m_ID = glCreateProgram());
		GLCall(glAttachShader(m_ID, vertexShader));
		GLCall(glAttachShader(m_ID, fragmentShader));
		GLCall(glLinkProgram(m_ID));
		GLCall(glGetProgramiv(m_ID, GL_LINK_STATUS, &result));
		if (result == GL_FALSE) {
			int length;
			GLCall(glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &length));
			char* message = (char*)alloca(length * sizeof(char));
			GLCall(glGetProgramInfoLog(m_ID, length, &length, message));
			std::string out = "Failed to link shader program : " + std::string(message);
			prx::Log::message(out, prx::LOG_WARNING);
			//ASSERT(false);
		}
		GLCall(glDeleteShader(vertexShader));
		GLCall(glDeleteShader(fragmentShader));
	}

	void Shader::loadUniforms() {
		int uniformCount;
		GLCall(glGetProgramiv(m_ID, GL_ACTIVE_UNIFORMS, &uniformCount));
		m_Uniforms.resize(uniformCount);
		char name[128];
		for (unsigned int i = 0; i < uniformCount; i++) {
			unsigned int glType;
			GLCall(glGetActiveUniform(m_ID, i, sizeof(name), nullptr, &m_Uniforms[i].size, &glType, name));
			m_Uniforms[i].name = std::string(name);
			m_Uniforms[i].type = glType;
			
			GLCall(m_Uniforms[i].location = glGetUniformLocation(m_ID, name));
		}
	}

	std::optional<int> Shader::getUniformLocation(std::string_view uniform) const {
		for (auto& element : m_Uniforms)
			if (element.name == uniform)
				return element.location;
		return std::nullopt;
	}

	// Set uniform to a current bound shader
	// !!!! BIND SHADER BEFORE CALL THIS !!!!
	void Shader::setUniform(const std::string& uniformName, hpm::mat4 mat) {
		auto loc = getUniformLocation(uniformName);
		if (loc) {
			GLCall(glUniformMatrix4fv(loc.value(), 1, GL_FALSE, mat.elems));
		}
		else {
			prx::Log::message("Can not set uniform. Invalid uniform name.", prx::LOG_WARNING);
		}
	}
	
	// Set uniform to a current bound shader
	/*void Shader::setUniform(const std::string & uniformName, hpm::mat3 mat) {
		auto loc = getUniformLocation(uniformName);
		if (loc) {
			GLCall(glUniformMatrix3fv(loc.value(), 1, GL_FALSE, &mat[0][0]));
		}
		else {
			prx::Log::message("Can not set uniform. Invalid uniform name.", prx::LOG_WARNING);
		}
	}*/

	void Shader::setUniform(const std::string& uniformName, hpm::vec2 vec) {
		auto loc = getUniformLocation(uniformName);
		if (loc) {
			GLCall(glUniform2f(loc.value(), vec.x, vec.y));
		}
		else {
			prx::Log::message("Can not set uniform. Invalid uniform name.", prx::LOG_WARNING);
		}
	}

	// Set uniform to a current bound shader
	void Shader::setUniform(const std::string& uniformName, hpm::vec3 vec) {
		auto loc = getUniformLocation(uniformName);
		if (loc) {
			GLCall(glUniform3f(loc.value(), vec.x, vec.y, vec.z));
		}
		else {
			prx::Log::message("Can not set uniform. Invalid uniform name.", prx::LOG_WARNING);
		}
	}

	// Set uniform to a current bound shader
	void Shader::setUniform(const std::string & uniformName, hpm::vec4 vec) {
		auto loc = getUniformLocation(uniformName);
		if (loc) {
			GLCall(glUniform4f(loc.value(), vec.x, vec.y, vec.z, vec.w));
		}
		else {
			prx::Log::message("Can not set uniform. Invalid uniform name.", prx::LOG_WARNING);
		}
	}

	// Set uniform to a current bound shader
	void Shader::setUniform(const std::string& uniformName, float floatNum) {
		auto loc = getUniformLocation(uniformName);
		if (loc) {
			GLCall(glUniform1f(loc.value(), floatNum));
		}
		else {
			prx::Log::message("Can not set uniform. Invalid uniform name.", prx::LOG_WARNING);
		}
	}

	// Set uniform to a current bound shader
	void Shader::setUniform(const std::string& uniformName, int intNum) {
		auto loc = getUniformLocation(uniformName);
		if (loc) {
			GLCall(glUniform1i(loc.value(), intNum));
		}
		else {
			prx::Log::message("Can not set uniform. Invalid uniform name.", prx::LOG_WARNING);
		}
	}

	// Set uniform to a current bound shader
	void Shader::setUniform(const std::string& uniformName, unsigned int uintNum) {
		auto loc = getUniformLocation(uniformName);
		if (loc) {
			GLCall(glUniform1i(loc.value(), uintNum));
		}
		else {
			prx::Log::message("Can not set uniform. Invalid uniform name.", prx::LOG_WARNING);
		}
	}

	void Shader::setUniform(const std::string& uniformName, float* floatArr, unsigned int count) {
		auto loc = getUniformLocation(uniformName);
		if (loc) {
			GLCall(glUniform1fv(loc.value(), count ,floatArr));
		}
		else {
			prx::Log::message("Can not set uniform. Invalid uniform name.", prx::LOG_WARNING);
		}
	}

	void Shader::setUniform(const std::string& uniformName, int* floatArr, unsigned int count) {
		auto loc = getUniformLocation(uniformName);
		if (loc) {
			GLCall(glUniform1iv(loc.value(), count, floatArr));
		}
		else {
			prx::Log::message("Can not set uniform. Invalid uniform name.", prx::LOG_WARNING);
		}
	}
}
