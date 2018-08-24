#pragma once
#ifndef _RESOURCES_H_
#define _RESOURCES_H_

#include <map>
#include <string_view>

#include "../shading/Shader.h"

namespace prx {

	class Resources {
	private:
		Resources();

		static std::map<unsigned int, Shader> m_Shaders;

	public:
		// Creates shader if it`s doesn`t exist yet and returns pointer to new created shader or existing shader from map.
		static prx::Shader* loadShader(std::string_view name, const std::string& vertexPath,
			const std::string& fragmentPath);
		// If shader exists returns pointer on it, otherwise returns nullptr
		static Shader* getShader(std::string_view name);
		static Shader* getShader(unsigned int hashName);

		static void deleteShader(std::string_view name);
		static void deleteShader(unsigned int hashName);
	};
}
#endif
