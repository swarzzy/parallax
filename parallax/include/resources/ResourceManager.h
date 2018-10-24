#pragma once
#include <map>
#include "../Common.h"
#include "../utils/Singleton.h"

namespace prx {

	class Font;
	class Texture;
	class Sound;
	class Resource;

	class ResourceManager final : public Singleton<ResourceManager> {
	public:
		friend class Singleton<ResourceManager>;
	private:
		PRX_DISALLOW_COPY_AND_MOVE(ResourceManager);

		ResourceManager() {};
		~ResourceManager() {};

	private:
		static std::map<prx_id_t, Resource>	m_Resources;

	public:
		template<typename Res, typename... Args>
		inline Res* get(prx_id_t identifier, Args&&... args);

	};

	template<typename Res, typename... Args>
	Res* ResourceManager::get(prx_id_t identifier, Args&&... args) {
		//auto resource = m_Resources.find(identifier);
		//if (resource != m_Resources.end()) {
		//	return &static_cast<Res>(resource->second);
		//}
		//// TODO: Check how many constructors this runs and make emplace
		//auto newResource = new Res(std::forward<Args>(args)...);
		//m_Resources.insert(std::move(std::pair<prx_id_t, Resource>(newResource.getIdentificator(), std::move(static_cast<Resource>(*newResource)))));
		//return newResource;
		return nullptr;
	}
}
