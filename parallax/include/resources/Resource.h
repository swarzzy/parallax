#pragma once
#include <string>
#include "../Common.h"
#include "../utils/SimpleHash.h"

namespace prx {

	template <typename T>
	class ResourceHandler;

	class Resource {
	private:
		inline static size_t _globalResourceCounter = 0;
	protected:
		size_t m_uID;
		size_t m_RefCounter;

		std::string m_Name;
		std::string m_FilePath;
		// An identifier (hashed filepath string) to distinguish unique and replicable resources
		prx_id_t m_ID;

		PRX_DISALLOW_COPY_AND_MOVE(Resource);

		explicit Resource(std::string_view name, std::string_view filepath)
		: m_uID(++_globalResourceCounter),
		  m_RefCounter(0),
		  m_Name(name),
		  m_FilePath(filepath),
		  m_ID(hash_string(filepath))
		{}

		virtual ~Resource() {};

	public:
		inline size_t getUniqueID() const noexcept;
		inline prx_id_t getID() const noexcept;
		inline const std::string& getName() const noexcept;
		inline const std::string& getFilePath() const noexcept;
		inline const prx_id_t getRefCount() const noexcept;
		static inline prx_id_t makeID(std::string_view filepath);

		template <typename T>
		friend class ResourceHandler;

		friend class ResourceManager;
	};

	inline size_t Resource::getUniqueID() const noexcept {
		return m_uID;
	}

	inline const std::string& Resource::getName() const noexcept {
		return m_Name;
	}


	inline const std::string& Resource::getFilePath() const noexcept {
		return m_FilePath;
	}

	inline const prx_id_t Resource::getRefCount() const noexcept {
		return m_RefCounter;
	}

	inline prx_id_t Resource::getID() const noexcept {
		return m_ID;
	}

	inline prx_id_t Resource::makeID(std::string_view filepath) {
		return hash_string(filepath);
	}

}
