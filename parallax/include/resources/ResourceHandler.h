#pragma once

#include "../Common.h"
#include "Resource.h"

namespace prx {

	template<typename Res>
	class ResourceHandler final {
	private:
		Res* m_Resource;

		inline explicit ResourceHandler(Res* resource);
	public:
		template <typename ResType, typename... Args>
		inline friend ResourceHandler<ResType> get_resource(Args&&... args);
		
		inline ~ResourceHandler();

		inline explicit ResourceHandler(const ResourceHandler& other) noexcept;
		inline explicit ResourceHandler(ResourceHandler&& other) noexcept;
		inline ResourceHandler& operator=(const ResourceHandler& other) noexcept;
		ResourceHandler& operator=(ResourceHandler&& other) noexcept;

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
		inline Res* get() noexcept;
		inline size_t getRefCount() const noexcept;
		inline bool unique() const noexcept;
	public:
		ResourceHandler(const ResourceHandler&& other) = delete;
		ResourceHandler& operator=(const ResourceHandler&& other) = delete;
	};

	template <typename ResType, typename... Args>
	ResourceHandler<ResType> get_resource(Args&&... args) {
		// TODO: resource manager
		return ResourceHandler<ResType>(new ResType(std::forward<Args>(args)...));
	}

	template <typename Res>
	ResourceHandler<Res>::ResourceHandler(Res* resource) {
		if (resource == nullptr) {
			m_Resource = nullptr;
		}
		else {
			m_Resource = resource;
			++m_Resource->m_RefCounter;
		}
		PRX_WARN(m_Resource != nullptr ? m_Resource->m_RefCounter : 300, " constructed");
	}

	template <typename Res>
	ResourceHandler<Res>::~ResourceHandler() {
		// TODO: resource manager
		if (m_Resource != nullptr) {
			--m_Resource->m_RefCounter;
		}
		PRX_WARN(m_Resource != nullptr ? m_Resource->m_RefCounter : 300, " deleted");
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
		PRX_WARN(m_Resource != nullptr ? m_Resource->m_RefCounter : 300, " copied");
	}

	template <typename Res>
	ResourceHandler<Res>::ResourceHandler(ResourceHandler&& other) noexcept {
		if (other.m_Resource == nullptr) {
			m_Resource = nullptr;
		} else {
			m_Resource = other.m_Resource;
			other.m_Resource = nullptr;
		}
		PRX_WARN(m_Resource != nullptr ? m_Resource->m_RefCounter : 300, " moved");
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
		PRX_WARN(m_Resource != nullptr ? m_Resource->m_RefCounter : 300, " copy assign");
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
		PRX_WARN(m_Resource != nullptr ? m_Resource->m_RefCounter : 300, " move assign");
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
	Res* ResourceHandler<Res>::get() noexcept {
		return m_Resource;
	}

	template<typename Res>
	size_t ResourceHandler<Res>::getRefCount() const noexcept {
		if (m_Resource == nullptr) {
			return 0;
		}
		else {
			return m_Resource->m_RefCount;
		}
	}

	template<typename Res>
	bool ResourceHandler<Res>::unique() const noexcept {
		return m_Resource != nullptr && m_Resource->m_RefCounter == 1;
	}

}