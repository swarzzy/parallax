#pragma once
// *******************************************
// Parallax Engine vertex buffer layout v1.1
// *******************************************
//
// ===========================
// REQUIRED OPENGL API VERSION
// ===========================
// API Independent (Except macros and constants)
//
// ====================
// API BREAKING CHANGES
// ====================
// Major changes that breaks whole API and some client code need to be changed
//
// 2018-11-17:	Rewrote the whole class. Layouts now used in Vertex buffers directly. 
//
// =====
// TODO:
// =====
// -- Get rid of GLEW include in header
// -- Support more types

#include<vector>
#include "../../ext/GL/glew.h"
#include "../../utils/log/Log.h"

namespace prx {

	struct VertexBufferElement {
		unsigned int type;
		unsigned int count;
		unsigned char normalized;
	};

	class VertexBufferLayout {
	private:
		std::vector<VertexBufferElement> m_Elements;
		unsigned int m_Stride;
	public:
		VertexBufferLayout()
			:m_Stride(0) 
		{}

		template<typename T>
		void push(unsigned int count) {
			PRX_ERROR("VERTEX BUFFER LAYOUT: Incompatible with vertex buffer type");
		}
		template<>
		void push<float>(unsigned int count) {
			m_Elements.push_back({ GL_FLOAT, count, false });
			m_Stride += sizeof(GLfloat) * count;
		}
		template<>
		void push<unsigned int>(unsigned int count) {
			m_Elements.push_back({ GL_UNSIGNED_INT, count, false });
			m_Stride += sizeof(GLuint)* count;
		}
		template<>
		void push<byte>(unsigned int count) {
			m_Elements.push_back({ GL_UNSIGNED_BYTE, count, true });
			m_Stride += sizeof(GLbyte) * count;
		}
		inline unsigned int getStride() const { return m_Stride; }
		inline const std::vector<VertexBufferElement>& getElements() const { return  m_Elements; }
	};
}