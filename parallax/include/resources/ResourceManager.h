#pragma once
#include <unordered_map>
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
		std::unordered_map<prx_id_t, Resource*>	m_Resources;
		std::vector<prx_id_t> m_GarbageList;

	public:
		template<typename Res>
		inline Res* load(std::string_view filepath);

		template<typename Res>
		inline Res* get(std::string_view filepath);

		template<typename Res>
		inline void free(Res* resource);

		inline void collectGarbage();

	};

	template<typename Res>
	Res* ResourceManager::load(std::string_view filepath) {
		Res* resource = new Res(filepath);
		Resource* ptr = dynamic_cast<Resource*>(resource);
		if (ptr == nullptr) {
			PRX_ERROR("RESOURCE MANAGER: Failed to load resource! Unknown resource type.\n-> TYPE: ",
				typeid(Res).name());
			delete resource;
			return nullptr;
			// TODO: EXCEPTIONS
		}
		auto result = m_Resources.emplace(ptr->getResID(), ptr);
		if (!result.second) {
			PRX_ERROR("RESOURCE MANAGER: Failed to load resource! Unexpected error.");
			// TODO: EXCEPTIONS
			delete resource;
			return nullptr;
		}
		++resource->m_RefCounter;
		return resource;
	}

	template<typename Res>
	inline Res* ResourceManager::get(std::string_view filepath) {
		auto result = m_Resources.find(Resource::makeResID(filepath));
		if (result == m_Resources.end())
			return nullptr;
		Res* ptr;
		if (ptr = dynamic_cast<Res*>(result->second)) {
			++ptr->m_RefCounter;
			return ptr;
		}
		if (ptr->getRefCount() <= 0) {
			// Very slow thing
			auto result = std::find(m_GarbageList.begin(), m_GarbageList.end(), ptr->getResID());
			m_GarbageList.erase(result);
		}
		return nullptr;
	}

	template<typename Res>
	void ResourceManager::free(Res* resource) {
		--resource->m_RefCounter;
		if (resource->m_RefCounter <= 0) {
#ifdef PARALLAX_DEBUG
			if (resource->m_RefCounter < 0)
				PRX_WARN("RESOURCE MANAGER: Reference counter is less than zero!");
#endif
			m_GarbageList.push_back(resource->getResID());
		}
	}

	void ResourceManager::collectGarbage() {
#ifdef PARALLAX_ENABLE_MEMORY_LOGGING
		unsigned int counter = 0;
		for (auto garbage : m_GarbageList) {
			m_Resources.erase(garbage);
			counter++;
		}
		PRX_INFO("GARBAGE COLLECTION: ", counter, " items deleted.");
#else
		for (auto garbage : m_GarbageList) {
				m_Resources.erase(garbage);
		}
#endif
	}
}