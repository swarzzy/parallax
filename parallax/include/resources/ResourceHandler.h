#pragma once

#include "Resource.h"
#include "ResourceManager.h"

namespace prx {
	template<typename Res>
	class ResourceHandler final {
	private:
		static struct weak_construct_t {};
		static constexpr weak_construct_t weak_construct = weak_construct_t();

		Res* m_Resource;
		inline explicit ResourceHandler(weak_construct_t, Res* resource);
	public:
		template <typename T>
		inline friend ResourceHandler<T> get_resource(std::string_view filepath);
		
		inline explicit ResourceHandler(Res* resource);
		inline ~ResourceHandler();

		inline ResourceHandler(const ResourceHandler& other) noexcept;
		inline ResourceHandler(ResourceHandler& other) noexcept;
		inline ResourceHandler(const ResourceHandler&& other) noexcept;
		inline ResourceHandler(ResourceHandler&& other) noexcept;
		inline ResourceHandler& operator=(const ResourceHandler& other) noexcept;
		inline ResourceHandler& operator=(ResourceHandler& other) noexcept;
		inline ResourceHandler& operator=(ResourceHandler&& other) noexcept;
		inline ResourceHandler& operator=(const ResourceHandler&& other) noexcept;

		template <typename L, typename R>
		inline friend bool operator==(const ResourceHandler<L>& left, const ResourceHandler<R>& right) noexcept;
		template <typename L>
		inline friend bool operator==(const ResourceHandler<L>& left, std::nullptr_t right) noexcept;
		template <typename R>
		inline friend bool operator==(std::nullptr_t left, const ResourceHandler<R>& right) noexcept;
		template <typename L, typename R>
		inline friend bool operator!=(const ResourceHandler<L>& left, const ResourceHandler<R>& right) noexcept;
		template <typename L>
		inline friend bool operator!=(const ResourceHandler<L>& left, std::nullptr_t right) noexcept;
		template <typename R>
		inline friend bool operator!=(std::nullptr_t left, const ResourceHandler<R>& right) noexcept;

		inline operator bool() const noexcept;

		Res* operator->() noexcept;

		inline void free() noexcept;
		inline Res* get() const noexcept;
		inline size_t getRefCount() const noexcept;
		inline bool unique() const noexcept;
	};

	template <typename T>
	ResourceHandler<T> get_resource(std::string_view filepath) {
		T* result = ResourceManager::getInstance()->get<T>(filepath);
		if (result == nullptr) {
			result = ResourceManager::getInstance()->load<T>(filepath);
			if (result == nullptr) {
				PRX_ERROR("RESOURCE MANAGER: Failed to load resource\n-> PATH: ", filepath);
			}
		}
		return ResourceHandler<T>(ResourceHandler<T>::weak_construct, result);
	}

	template <typename Res>
	ResourceHandler<Res>::ResourceHandler(weak_construct_t, Res* resource)
		: m_Resource(resource)
	{}

	template <typename Res>
	ResourceHandler<Res>::ResourceHandler(Res* resource) 
		: m_Resource(resource) 
	{
		if (m_Resource != nullptr) {
			++m_Resource->m_RefCounter;
		}
	}

	template <typename Res>
	ResourceHandler<Res>::~ResourceHandler() {
		if (m_Resource != nullptr) {
			ResourceManager::getInstance()->free(m_Resource);
		}
	}

	template <typename Res>
	ResourceHandler<Res>::ResourceHandler(const ResourceHandler& other) noexcept {
		if (other.m_Resource == nullptr) {
			m_Resource = nullptr;
		}
		else {
			m_Resource = other.m_Resource;
			++m_Resource->m_RefCounter;
		}
	}

	template <typename Res>
	ResourceHandler<Res>::ResourceHandler(ResourceHandler& other) noexcept {
		if (other.m_Resource == nullptr) {
			m_Resource = nullptr;
		}
		else {
			m_Resource = other.m_Resource;
			++m_Resource->m_RefCounter;
		}
	}

	template <typename Res>
	ResourceHandler<Res>::ResourceHandler(ResourceHandler&& other) noexcept {
		if (other.m_Resource == nullptr) {
			m_Resource = nullptr;
		} else {
			m_Resource = other.m_Resource;
			other.m_Resource = nullptr;
		}
	}

	template <typename Res>
	ResourceHandler<Res>& ResourceHandler<Res>::operator=(const ResourceHandler& other) noexcept {
		if (other != *this) {
			if (other.m_Resource == nullptr) {
				m_Resource = nullptr;
			}
			else {
				this->m_Resource = other.m_Resource;
				++this->m_Resource->m_RefCounter;
			}
		}
		return *this;
	}

	template <typename Res>
	ResourceHandler<Res>& ResourceHandler<Res>::operator=(ResourceHandler& other) noexcept {
		if (other != *this) {
			if (other.m_Resource == nullptr) {
				m_Resource = nullptr;
			}
			else {
				this->m_Resource = other.m_Resource;
				++this->m_Resource->m_RefCounter;
			}
		}
		return *this;
	}

	template <typename Res>
	ResourceHandler<Res>& ResourceHandler<Res>::operator=(ResourceHandler&& other) noexcept {
		if (other != *this) {
			if (other.m_Resource == nullptr) {
				m_Resource = nullptr;
			}
			else {
				this->m_Resource = other.m_Resource;
				other.m_Resource = nullptr;
			}
		}
		return *this;
	}

	template <typename Res>
	ResourceHandler<Res>::ResourceHandler(const ResourceHandler&& other) noexcept {
		if (other.m_Resource == nullptr) {
			m_Resource = nullptr;
		}
		else {
			m_Resource = other.m_Resource;
			++m_Resource->m_RefCounter;
		}
	}

	template <typename Res>
	ResourceHandler<Res>& ResourceHandler<Res>::operator=(const ResourceHandler&& other) noexcept {
		if (other != *this) {
			if (other.m_Resource == nullptr) {
				m_Resource = nullptr;
			}
			else {
				this->m_Resource = other.m_Resource;
				++this->m_Resource->m_RefCounter;
			}
		}
		return *this;
	}

	template <typename L, typename R>
	inline bool operator==(const ResourceHandler<L>& left, const ResourceHandler<R>& right) noexcept {
		return left.m_Resource == right.m_Resource;
	}

	template <typename L, typename R>
	inline bool operator!=(const ResourceHandler<L>& left, const ResourceHandler<R>& right) noexcept {
		return left.m_Resource != right.m_Resource;
	}

	template <typename L>
	bool operator==(const ResourceHandler<L>& left, std::nullptr_t right) noexcept {
		return left.m_Resource == right;
	}

	template <typename R>
	bool operator==(std::nullptr_t left, const ResourceHandler<R>& right) noexcept {
		return left == right.m_Resource;
	}

	template <typename L>
	bool operator!=(const ResourceHandler<L>& left, std::nullptr_t right) noexcept {
		return left.m_Resource != right;
	}

	template <typename R>
	bool operator!=(std::nullptr_t left, const ResourceHandler<R>& right) noexcept {
		 return left != right.m_Resource;
	}

	template <typename Res>
	ResourceHandler<Res>::operator bool() const noexcept {
		return static_cast<bool>(m_Resource);
	}

	template <typename Res>
	Res* ResourceHandler<Res>::operator->() noexcept {
		return m_Resource;
	}

	template <typename Res>
	void ResourceHandler<Res>::free() noexcept {
		if (m_Resource != nullptr) {
			--m_Resource->m_RefCounter;
			m_Resource = nullptr;
		}		
	}

	template<typename Res>
	Res* ResourceHandler<Res>::get() const noexcept {
		return m_Resource;
	}

	template<typename Res>
	size_t ResourceHandler<Res>::getRefCount() const noexcept {
		if (m_Resource == nullptr) {
			return 0;
		}
		else {
			return m_Resource->getRefCount();
		}
	}

	template<typename Res>
	bool ResourceHandler<Res>::unique() const noexcept {
		return m_Resource != nullptr && m_Resource->m_RefCounter == 1;
	}
}