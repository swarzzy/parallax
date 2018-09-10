//#include "Resources.h"
//
//#include "../utils/SimpleHash.h"
//
//namespace prx {
//	
//	std::map<unsigned int, Shader>	Resources::m_Shaders = std::map<unsigned int, Shader>();
//
//	ResourceHandler<Shader> Resources::loadShader(std::string_view name, std::string_view vertexPath, std::string_view fragmentPath) {
//		unsigned int id = SimpleHash::hashString(name);
//		auto element = m_Shaders.find(id);
//		if (element != m_Shaders.end())
//			return ResourceHandler<Shader>(&element->second, id);
//
//		auto result = m_Shaders.emplace(std::piecewise_construct, std::forward_as_tuple(id),
//			std::forward_as_tuple(vertexPath, fragmentPath));
//		return ResourceHandler<Shader>(&result.first->second, id);
//	}
//
//	template<typename T>
//	ResourceHandler<T> Resources::get(unsigned int id) {
//		Log::message("RESOURCE MANAGER: Incompatible resource type.", LOG_ERROR);
//		// TODO: use parallax debugger for this
//		static_assert(false);
//	}
//
//	template<>
//	ResourceHandler<Shader> Resources::get<Shader>(unsigned int id) {
//		auto element = m_Shaders.find(id);
//		if (element != m_Shaders.end())
//			return ResourceHandler<Shader>(&element->second, id);
//		Log::message("Resources: requested shaer object does not exist", LOG_WARNING);
//		return ResourceHandler<Shader>(nullptr, 0);
//	}
//
//	template<typename T>
//	void Resources::deleteRes(unsigned int id) {
//		Log::message("RESOURCE MANAGER: Incompatible resource type.", LOG_ERROR);
//		// TODO: use parallax debugger for this
//		static_assert(false);
//	}
//
//	template<>
//	void Resources::deleteRes<Shader>(unsigned int id) {
//#ifdef PARALLAX_DEBUG
//		unsigned int result = m_Shaders.erase(id);
//		if (result == 0)
//			Log::message("RESOURCE MANAGER: Can`t delete element. Element already deleted or never exist.", LOG_WARNING);
//#else
//		m_Shaders.erase(id);
//#endif
//	}
//}
#include "Resources.h"
namespace prx {
	std::map<unsigned int, internal::ResourceStorage<Shader>>	Resources::m_Shaders = std::map<unsigned int, internal::ResourceStorage<Shader>>();

	unsigned int Resources::loadShader(std::string_view name, std::string_view vertexPath, std::string_view fragmentPath) {
		unsigned int id = SimpleHash::hashString(name);
		auto element = m_Shaders.find(id);
		if (element != m_Shaders.end()) {
			Log::message("RESOURCE MANAGER: Shader already has been loaded.", LOG_WARNING);
			return id;
		}
		Shader* shader = new Shader(vertexPath, fragmentPath);
		auto result = m_Shaders.emplace(std::piecewise_construct, std::forward_as_tuple(id),
			std::forward_as_tuple(id, shader));
		return id;
	}
}