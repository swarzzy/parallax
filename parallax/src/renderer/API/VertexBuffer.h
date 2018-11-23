#pragma once
// ==================================
// Parallax Engine vertex buffer v1.1
// ==================================
//
// LOOK FOR DOCUMENTATION IN CPP FILE
//

#include "../../Common.h"
#include "VertexBufferLayout.h"

namespace prx {

	enum class BufferType {
		STATIC_DRAW,
		DYNAMIC_DRAW
	};

	class VertexBuffer {
		PRX_DISALLOW_COPY_AND_MOVE(VertexBuffer)
	private:
		unsigned int m_BufferHandle;
		BufferType m_Type;
		size_t m_Size;
		VertexBufferLayout m_Layout;
	public:
		VertexBuffer(BufferType type);
		~VertexBuffer();

		void bind();
		void unbind();

		void resize(size_t size);
		void setData(size_t size, const void* data);
		void setLayout(const VertexBufferLayout& layout);

		// Bind the buffer before get the pointer
		// Returns write-only pointer
		void* getPointer();
		void releasePointer();

		static uint getGLBufferType(BufferType type);
		static uint getSizeOfType(unsigned int type);
	};
}