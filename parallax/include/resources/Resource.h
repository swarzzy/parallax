#pragma once
#include "../Common.h"

namespace prx {
	class Resource {
	private:
		inline static size_t _globalResourceCounter = 0;
	private:
		size_t m_ID;
		size_t m_refCounter;

		PRX_DISALLOW_COPY_AND_MOVE(Resource);

		Resource();
		virtual ~Resource();
	};
}
