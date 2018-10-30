#pragma once

#include "../Common.h"

namespace prx {
	template<typename Class>
	class Singleton {
	protected:
		PRX_DISALLOW_COPY_AND_MOVE(Singleton)

		Singleton() {};
		virtual ~Singleton() {};

	private:
		
		inline static Class* m_Object = nullptr;
	public:
		template <typename... Args>
		inline static void initialize(Args&&... args);
		inline static Class* getInstance();
		inline static void destroy();
	};
}
#include "Singleton.inl"