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
		inline static void initialize();
		inline static Class* getInstance();
		inline static void destroy();
	};
}
#include "Singleton.inl"