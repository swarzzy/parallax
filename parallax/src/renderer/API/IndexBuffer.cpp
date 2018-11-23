// *******************************************
// Parallax Engine index buffer v1.1
// *******************************************
//
// ===========================
// REQUIRED OPENGL API VERSION
// ===========================
// Required OpenGL version: 3
// Required OpenGL ES version: 2
//
// ====================
// API BREAKING CHANGES
// ====================
// Major changes that breaks whole API and some client code need to be changed
//
// 2018-11-17:	Changed methods naming
//

#include "IndexBuffer.h"

#include "../../utils/error_handling/GLErrorHandler.h"
#include "../../ext/GL/glew.h"

namespace prx {

	IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
		: m_Count(count) 
	{
		// Do we need check for that
		PRX_ASSERT(sizeof(unsigned int) == sizeof(GLuint), "RENDERER API: Wrong unsigned int size");

		GLCall(glGenBuffers(1, &m_BufferHandle));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferHandle));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	IndexBuffer::~IndexBuffer() {
		GLCall(glDeleteBuffers(1, &m_BufferHandle));
	}

	void IndexBuffer::bind() const {
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferHandle));
	}

	void IndexBuffer::unbind() const {
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
}