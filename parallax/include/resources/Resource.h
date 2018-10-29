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
		size_t m_UsersCounter;	// Initializations counter
		bool   m_Initialized;

		std::string m_FilePath;
		// An identifier (hashed filepath string) to distinguish unique and replicable resources
		prx_id_t m_ID;

		PRX_DISALLOW_COPY_AND_MOVE(Resource);

		explicit Resource(std::string_view filepath);
		virtual ~Resource() {};

	public:
		inline size_t getUniqueID() const noexcept;
		inline prx_id_t getResID() const noexcept;
		inline const std::string& getFilePath() const noexcept;
		inline const prx_id_t getRefCount() const noexcept;
		inline size_t getUserCount() const noexcept;
		inline bool isInitialized() const noexcept;
		static inline prx_id_t makeResID(std::string_view filepath);

		// TODO: made this pure virtual
		virtual bool isInitialized() { return false; };

		void init();
		virtual void update() {};
		void destroy();

		template <typename T>
		friend class ResourceHandler;

		friend class ResourceManager;

	protected:
		virtual void initInternal() {};
		virtual void destroyInternal() {};
	};

	inline Resource::Resource(std::string_view filepath)
		: m_uID(++_globalResourceCounter),
		  m_RefCounter(0),
		  m_UsersCounter(0),
		  m_Initialized(false),
		  m_FilePath(filepath),
		  m_ID(hash_string(filepath))
	{}

	inline size_t Resource::getUniqueID() const noexcept {
		return m_uID;
	}

	inline const std::string& Resource::getFilePath() const noexcept {
		return m_FilePath;
	}

	inline const prx_id_t Resource::getRefCount() const noexcept {
		return m_RefCounter;
	}

	inline prx_id_t Resource::getResID() const noexcept {
		return m_ID;
	}

	inline prx_id_t Resource::makeResID(std::string_view filepath) {
		return hash_string(filepath);
	}

	inline size_t Resource::getUserCount() const noexcept {
		return m_UsersCounter;
	}

	inline bool Resource::isInitialized() const noexcept {
		return m_Initialized;
	}

	inline void Resource::init() {
		m_UsersCounter++;
		if (!m_Initialized) {
			m_Initialized = true;
			initInternal();
			PRX_INFO("Resource initialized\n-> FILE: ", m_FilePath);
		}
	}

	inline void Resource::destroy() {
		if (m_Initialized) {
			m_UsersCounter--;
			if (m_UsersCounter <= 0) {
				if (m_UsersCounter < 0)
					PRX_WARN("RESOURCE: User counter less than zero!\n-> PATH: ", m_FilePath);
				m_Initialized = false;
				destroyInternal();
				PRX_INFO("Resource destroyed\n-> FILE: ", m_FilePath);
			}
		}
	}



}
