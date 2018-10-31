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

	Shader::Shader(const ShaderSource& source) 
		: m_ShaderSource(source) {
		
		compileShader();
		loadUniforms();
	}

	Shader::~Shader() {
		GLCall(glDeleteProgram(m_ID));
	}

	void Shader::readShaderFromFile(std::string_view vertexPath, std::string_view fragmentPath) {

		std::optional<std::string> vertSrc = FileReader::readTextFile(vertexPath);
		std::optional<std::string> fragSrc = FileReader::readTextFile(fragmentPath);
		// TODO: handle file reading violation
		if (vertSrc)
			m_ShaderSource.vertexSource = vertSrc.value();
		else {
			Log::message(LOG_LEVEL::LOG_FATAL, "Can not read vertex shader source");
			// TODO: exceptions
			ASSERT(false);
		}
		if (fragSrc)
			m_ShaderSource.fragmentSource = fragSrc.value();
		else {
			Log::message(LOG_LEVEL::LOG_FATAL, "Can not read fragment shader source");
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
			PRX_FATAL("(Shader): Failed to compile vertex shader. Error:\n", message, "\n");
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
				PRX_FATAL("(Shader): Failed to compile fragment shader. Error:\n", message, "\n");
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
			PRX_FATAL("(Shader): Failed to link shader program. Error:\n", message);
		}
		GLCall(glDeleteShader(vertexShader));
		GLCall(glDeleteShader(fragmentShader));
	}

	void Shader::loadUniforms() {
		int uniformCount;
		GLCall(glGetProgramiv(m_ID, GL_ACTIVE_UNIFORMS, &uniformCount));
		m_Uniforms.resize(uniformCount);
		char name[128];
		for (int i = 0; i < uniformCount; i++) {
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
	void Shader::setUniform(std::string_view uniformName, hpm::mat4 mat) {
		auto loc = getUniformLocation(uniformName);
		if (loc) {
			GLCall(glUniformMatrix4fv(loc.value(), 1, GL_FALSE, mat.elems));
		}
		else {
			PRX_ERROR("(Shader): Could not set uniform with name ", uniformName, 
					  ". In shader with OpenGL ID = ", m_ID, ".");
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

	void Shader::setUniform(std::string_view uniformName, hpm::vec2 vec) {
		auto loc = getUniformLocation(uniformName);
		if (loc) {
			GLCall(glUniform2f(loc.value(), vec.x, vec.y));
		}
		else {
			PRX_ERROR("(Shader): Could not set uniform with name ", uniformName,
					  ". In shader with OpenGL ID = ", m_ID, ".");
		}
	}

	// Set uniform to a current bound shader
	void Shader::setUniform(std::string_view uniformName, hpm::vec3 vec) {
		auto loc = getUniformLocation(uniformName);
		if (loc) {
			GLCall(glUniform3f(loc.value(), vec.x, vec.y, vec.z));
		}
		else {
			PRX_ERROR("(Shader): Could not set uniform with name ", uniformName,
					  ". In shader with OpenGL ID = ", m_ID, ".");
		}
	}

	// Set uniform to a current bound shader
	void Shader::setUniform(std::string_view uniformName, hpm::vec4 vec) {
		auto loc = getUniformLocation(uniformName);
		if (loc) {
			GLCall(glUniform4f(loc.value(), vec.x, vec.y, vec.z, vec.w));
		}
		else {
			PRX_ERROR("(Shader): Could not set uniform with name ", uniformName,
					  ". In shader with OpenGL ID = ", m_ID, ".");
		}
	}

	// Set uniform to a current bound shader
	void Shader::setUniform(std::string_view uniformName, float floatNum) {
		auto loc = getUniformLocation(uniformName);
		if (loc) {
			GLCall(glUniform1f(loc.value(), floatNum));
		}
		else {
			PRX_ERROR("(Shader): Could not set uniform with name ", uniformName,
					  ". In shader with OpenGL ID = ", m_ID, ".");
		}
	}

	// Set uniform to a current bound shader
	void Shader::setUniform(std::string_view uniformName, int intNum) {
		auto loc = getUniformLocation(uniformName);
		if (loc) {
			GLCall(glUniform1i(loc.value(), intNum));
		}
		else {
			PRX_ERROR("(Shader): Could not set uniform with name ", uniformName,
					  ". In shader with OpenGL ID = ", m_ID, ".");
		}
	}

	// Set uniform to a current bound shader
	void Shader::setUniform(std::string_view uniformName, unsigned int uintNum) {
		auto loc = getUniformLocation(uniformName);
		if (loc) {
			GLCall(glUniform1i(loc.value(), uintNum));
		}
		else {
			PRX_ERROR("(Shader): Could not set uniform with name ", uniformName,
					  ". In shader with OpenGL ID = ", m_ID, ".");
		}
	}

	void Shader::setUniform(std::string_view uniformName, float* floatArr, unsigned int count) {
		auto loc = getUniformLocation(uniformName);
		if (loc) {
			GLCall(glUniform1fv(loc.value(), count ,floatArr));
		}
		else {
			PRX_ERROR("(Shader): Could not set uniform with name ", uniformName,
					  ". In shader with OpenGL ID = ", m_ID, ".");
		}
	}

	void Shader::setUniform(std::string_view uniformName, int* floatArr, unsigned int count) {
		auto loc = getUniformLocation(uniformName);
		if (loc) {
			GLCall(glUniform1iv(loc.value(), count, floatArr));
		}
		else {
			PRX_ERROR("(Shader): Could not set uniform with name ", uniformName,
					  ". In shader with OpenGL ID = ", m_ID, ".");
		}
	}
}
