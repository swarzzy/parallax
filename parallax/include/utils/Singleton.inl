#include "log/Log.h"

namespace prx {
	template <typename Class>
	template <typename... Args>
	void Singleton<Class>::initialize(Args&&... args) {
		if (m_Object != nullptr)
			PRX_ERROR("Trying to create more than one copy of singleton.\n-> CLASS: ",
						typeid(Class).name());
		else
			m_Object = new Class(std::forward<Args>(args)...);
	}

	template <typename Class>
	Class* Singleton<Class>::getInstance() {
		PRX_ASSERT((m_Object != nullptr), "Attempt to get an instance of not initialized singleton.\n-> CLASS: ",
						typeid(Class).name());
		return m_Object;
	}

	template <typename Class>
	void Singleton<Class>::destroy() {
		delete m_Object;
		m_Object = nullptr;
	}
}
