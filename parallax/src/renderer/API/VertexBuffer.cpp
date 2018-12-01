// *******************************************
// Parallax Engine vertex buffer v1.1
// *******************************************
//
// ===========================
// REQUIRED OPENGL API VERSION
// ===========================
// Required OpenGL version: 3
// Required OpenGL ES version: NOT SUPPORTED (glMapBuffer)
//
// ====================
// API BREAKING CHANGES
// ====================
// Major changes that breaks whole API and some client code need to be changed
//
// 2018-11-17:	Rewrote the whole class. Add mapping and unmapping. 
//				Vertex buffers doesn`t use vertex arrays now
//
// =====
// TODO:
// =====
// -- Pointer access
// -- Replace glBufferData to glBufferSubData
// -- Cleanup bindings in all buffers

#include "VertexBuffer.h"

#include "../../utils/error_handling/GLErrorHandler.h"
#include <GL/gl3w.h>

// Disabling reinterpret_cast warnings
#pragma warning(push)
#pragma warning(disable:4312)

namespace prx {

	VertexBuffer::VertexBuffer(BufferType type) 
		: m_Type(type)
		, m_Size(0)
	{
		GLCall(glGenBuffers(1, &m_BufferHandle));
	}

//-----------------------------------------------------------------------------

	VertexBuffer::~VertexBuffer() {
		GLCall(glDeleteBuffers(1, &m_BufferHandle));
	}

//-----------------------------------------------------------------------------

	void VertexBuffer::resize(size_t size) {
		m_Size = size;

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_BufferHandle));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, nullptr, getGLBufferType(m_Type)));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

//-----------------------------------------------------------------------------

	void VertexBuffer::setData(size_t size, const void* data) {
		m_Size = size;
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_BufferHandle));
		GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

//-----------------------------------------------------------------------------

	void VertexBuffer::setLayout(const VertexBufferLayout& layout) {
		m_Layout = layout;
		const auto& elements = layout.getElements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++) {
			GLCall(glEnableVertexAttribArray(i));
			GLCall(glVertexAttribPointer(i, elements[i].count, elements[i].type, elements[i].normalized, 
										 layout.getStride(), reinterpret_cast<void*>(offset)));
			offset += elements[i].count * getSizeOfType(elements[i].type);
		}
	}

//-----------------------------------------------------------------------------

	void* VertexBuffer::getPointer() {
		void* pointer;
		GLCall(pointer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
		return pointer;
	}

//-----------------------------------------------------------------------------

	void VertexBuffer::releasePointer() {
		GLCall(glUnmapBuffer(GL_ARRAY_BUFFER));
	}

//-----------------------------------------------------------------------------

	unsigned VertexBuffer::getGLBufferType(BufferType type) {
		switch(type) {
		case BufferType::STATIC_DRAW: { return GL_STATIC_DRAW; }
		case BufferType::DYNAMIC_DRAW: {return GL_DYNAMIC_DRAW; }
		default: {PRX_FATAL("VERTEX BUFFER: Unknown buffer type."); }
		}
		// Dummy return to get rid of warning
		return 0;
	}

//-----------------------------------------------------------------------------

	unsigned VertexBuffer::getSizeOfType(unsigned type) {
		switch (type) {
		case GL_FLOAT:			{ return sizeof(GLfloat);}
		case GL_UNSIGNED_INT:	{ return sizeof(GLuint); }
		case GL_UNSIGNED_BYTE:	{ return sizeof(GLubyte);}
		default: {PRX_FATAL("VERTEX BUFFER: Unknown OpenGL type"); }
		}
		// Dummy return to get rid of warning
		return 0;
	}

//-----------------------------------------------------------------------------

	void VertexBuffer::bind() {
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_BufferHandle));
		setLayout(m_Layout);
	}

//-----------------------------------------------------------------------------

	void VertexBuffer::unbind() {
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
}
#pragma warning(pop)