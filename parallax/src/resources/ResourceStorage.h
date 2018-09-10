#pragma once
#ifndef _PARALLAX_RESOURCES_RESOURCE_STORAGE_H_
#define _PARALLAX_RESOURCES_RESOURCE_STORAGE_H_

namespace prx {
	template<typename T>
	class ResourceHandler;
}

namespace prx::internal {
	template<typename T>
	class ResourceStorage {
	private:
		unsigned short m_RefCounter;
		unsigned int m_ID;
		T* m_Resource;

	public:
		ResourceStorage(unsigned int id, T* resource)
			:m_RefCounter(0), m_ID(id), m_Resource(resource) {};

	public:
		friend class prx::ResourceHandler<T>;
	};
}
#endif
