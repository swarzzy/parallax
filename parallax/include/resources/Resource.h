#pragma once
#include <string>
#include "../Common.h"

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
		// An identifier to distinguish unique and replicable resources
		prx_id_t m_Identificator;

		PRX_DISALLOW_COPY_AND_MOVE(Resource);

		explicit Resource(std::string_view name, std::string_view filepath, prx_id_t identificator) 
		: m_uID(++_globalResourceCounter),
		  m_RefCounter(0),
		  m_Name(name),
		  m_FilePath(filepath),
		  m_Identificator(identificator)
		{}

		virtual ~Resource() {};

	public:
		inline size_t getUniqueID() const noexcept;
		inline prx_id_t getIdentificator() const noexcept;
		inline const std::string& getName() const noexcept;
		inline const std::string& getFilePath() const noexcept;

		template <typename T>
		friend class ResourceHandler;
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

	inline prx_id_t Resource::getIdentificator() const noexcept {
		return m_Identificator;
	}


}
