//#pragma once
//#ifndef _PARALLAX_RESOURCES_RESOURCE_HANDLER_H_
//#define _PARALLAX_RESOURCES_RESOURCE_HANDLER_H_
//
//#include "ResourceStorage.h"
//#include "Resources.h"
//
//namespace prx {
//	//class Resources;
//
//	template<typename T>
//	class ResourceHandler {
//	public:
//		
//		internal::ResourceStorage<T>*	m_ResourceStorage;
//	
//	public:
//		ResourceHandler();
//		ResourceHandler(T* resource,  unsigned int id);
//		~ResourceHandler();
//
//		ResourceHandler<T>& operator=(const ResourceHandler<T>& handler);
//		T* operator->();
//	};
//
//	template <typename T>
//	ResourceHandler<T>::ResourceHandler()
//		: m_ResourceStorage(new prx::internal::ResourceStorage<T>(0, nullptr)) {}
//
//	template <typename T>
//	ResourceHandler<T>::ResourceHandler(T* resource, unsigned id) 
//		: m_ResourceStorage(new prx::internal::ResourceStorage<T>(id, resource)){}
//
//	template <typename T>
//	ResourceHandler<T>::~ResourceHandler() {
//		m_ResourceStorage->m_RefCounter--;
//		if (m_ResourceStorage->m_RefCounter == 0) {
//			Resources::deleteRes<T>(m_ResourceStorage->m_ID);
//			delete m_ResourceStorage;
//			
//		}
//	}
//	
//	template <typename T>
//	ResourceHandler<T>& ResourceHandler<T>::operator=(const ResourceHandler<T>& handler) {
//		m_ResourceStorage = handler.m_ResourceStorage;
//		m_ResourceStorage->m_RefCounter++;
//		return this;
//	}
//
//	template <typename T>
//	T* ResourceHandler<T>::operator->() {
//		return m_ResourceStorage->m_Resource;
//	}
//}
//#endif
