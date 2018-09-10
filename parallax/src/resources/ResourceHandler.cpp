//#include "ResourceHandler.h"
//
//#include "Resources.h"
//
//namespace prx {
//	
//	
//
//	template <typename T>
//	ResourceHandler<T>::ResourceHandler(T* resource, unsigned int id) 
//		: m_ResourceStorage(new prx::internal::ResourceStorage<T>(id, resource)) {}
//
//	template <typename T>
//	ResourceHandler<T>::~ResourceHandler() {
//		m_ResourceStorage->m_RefCounter--;
//		if (m_ResourceStorage->m_RefCounter == 0) {
//			Resources::deleteRes<T>(m_ResourceStorage->m_ID);
//			delete m_ResourceStorage;
//		}
//	}
//
//	template <typename T>
//	ResourceHandler<T>& ResourceHandler<T>::operator=(const ResourceHandler<T>& handler) {
//		m_ResourceStorage = handler.m_ResourceStorage;
//		m_ResourceStorage->m_RefCounter++;
//	}
//
//	template <typename T>
//	T* ResourceHandler<T>::operator->() {
//		return m_ResourceStorage->m_Resource;
//	}
//}
