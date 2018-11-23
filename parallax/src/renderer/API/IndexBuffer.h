#pragma once
// ==================================
// Parallax Engine index buffer v1.1
// ==================================
//
// LOOK FOR DOCUMENTATION IN CPP FILE
//

#include "../../Common.h"

namespace prx {

	class IndexBuffer {
		PRX_DISALLOW_COPY_AND_MOVE(IndexBuffer)
	private:
		unsigned int m_BufferHandle;
		unsigned int m_Count;
	public:
		IndexBuffer(const unsigned int* data, unsigned int count);
		~IndexBuffer();

		void bind() const;
		void unbind() const;
		inline unsigned int getCount() const { return m_Count; };
	};
}
