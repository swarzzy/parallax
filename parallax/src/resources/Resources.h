#pragma once
#ifndef _PARALLAX_RESOURCES_RESOURCES_H_
#define _PARALLAX_RESOURCES_RESOURCES_H_

#include<map>

#include "../shading/Shader.h"
#include "../utils/SimpleHash.h"
#include "ResourceStorage.h"

namespace prx {
	
	template<typename T>
	class ResourceHandler {
	public:

		internal::ResourceStorage<T>*	m_ResourceStorage;

	public:
		ResourceHandler();
		ResourceHandler(internal::ResourceStorage<T>* resource);
		ResourceHandler(const ResourceHandler<T>& resourceHandler);
		~ResourceHandler();

		ResourceHandler<T>& operator=(const ResourceHandler<T>& handler);
		T* operator->();

	public:
		friend class Resources;

	private:
		unsigned short* getRefCounter();
	};
	
	class Resources {
	private:
		Resources();
		static std::map<unsigned int, internal::ResourceStorage<Shader>> m_Shaders;
	public:
		static bool init();
		static unsigned int loadShader(std::string_view name, std::string_view vertexPath, std::string_view fragmentPath);

		template<typename T>
		static ResourceHandler<T> get(unsigned int id);

		template<>
		static ResourceHandler<Shader> get<Shader>(unsigned int id);

		template<typename T>
		static void deleteRes(unsigned int id);

		template<>
		static void deleteRes<Shader>(unsigned int id);
		
	};

	//---------------------------------------------------------------------------------------------------------
	// ResourceHandler

	template <typename T>
	ResourceHandler<T>::ResourceHandler()
		: m_ResourceStorage(nullptr) {}

	template <typename T>
	ResourceHandler<T>::ResourceHandler(internal::ResourceStorage<T>* resource)
		: m_ResourceStorage(resource) {
		m_ResourceStorage->m_RefCounter++;
	}

	template <typename T>
	ResourceHandler<T>::ResourceHandler(const ResourceHandler<T>& resourceHandler) {
		m_ResourceStorage = resourceHandler.m_ResourceStorage;
		m_ResourceStorage->m_RefCounter++;
	}

	template <typename T>
	ResourceHandler<T>::~ResourceHandler() {
		m_ResourceStorage->m_RefCounter--;
		if (m_ResourceStorage->m_RefCounter == 0) {
			Resources::deleteRes<T>(m_ResourceStorage->m_ID);
		}
	}

	template <typename T>
	ResourceHandler<T>& ResourceHandler<T>::operator=(const ResourceHandler<T>& handler) {
		m_ResourceStorage = handler.m_ResourceStorage;
		m_ResourceStorage->m_RefCounter++;
		return this;
	}

	template <typename T>
	T* ResourceHandler<T>::operator->() {
		return m_ResourceStorage->m_Resource;
	}

	template <typename T>
	unsigned short* ResourceHandler<T>::getRefCounter() {
		return &m_ResourceStorage->m_ID;
	}

	//---------------------------------------------------------------------------------------------------------
	// Resources

	template<typename T>
	ResourceHandler<T> Resources::get(unsigned int id) {
		Log::message("RESOURCE MANAGER: Incompatible resource type.", LOG_ERROR);
		// TODO: use parallax debugger for this
		static_assert(false);
	}

	template<>
	ResourceHandler<Shader> Resources::get<Shader>(unsigned int id) {
		auto element = m_Shaders.find(id);
		if (element != m_Shaders.end())
			return ResourceHandler<Shader>(&element->second);
		Log::message("Resources: requested shader object does not exist", LOG_WARNING);
		return ResourceHandler<Shader>(nullptr);
	}

	template<typename T>
	void Resources::deleteRes(unsigned int id) {
		Log::message("RESOURCE MANAGER: Incompatible resource type.", LOG_ERROR);
		// TODO: use parallax debugger for this
		static_assert(false);
	}

	template<>
	void Resources::deleteRes<Shader>(unsigned int id) {
#ifdef PARALLAX_DEBUG
		unsigned int result = m_Shaders.erase(id);
		if (result == 0)
			Log::message("RESOURCE MANAGER: Can`t delete element. Element already deleted or never exist.", LOG_WARNING);
#else
		m_Shaders.erase(id);
#endif
	}
}
#endif
