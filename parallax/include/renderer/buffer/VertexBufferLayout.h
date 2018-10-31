#pragma once
#ifndef _VERTEXBUFFERLAYOUT_H_
#define _VERTEXBUFFERLAYOUT_H_

#include<vector>
#include <ext/GL/glew.h>

namespace prx {

	struct VertexBufferElement {
		unsigned int type;
		unsigned int count;
		unsigned char normalized;

		static unsigned int GetSizeOfType(unsigned int type) {
			switch (type) {
			case GL_FLOAT:			return sizeof(GLfloat);
			case GL_UNSIGNED_INT:	return sizeof(GLuint);
			case GL_UNSIGNED_BYTE:	return sizeof(GLubyte);
			}
			return 0;
		}
	};

	class VertexBufferLayout {
	private:
		std::vector<VertexBufferElement> m_Elements;
		unsigned int m_Stride;
	public:
		VertexBufferLayout()
			:m_Stride(0) {};

		template<typename T>
		void Push(unsigned int count) {
			static_assert(false);
		}
		template<>
		void Push<float>(unsigned int count) {
			m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
			m_Stride += sizeof(GLfloat) * count;
		}
		template<>
		void Push<unsigned int>(unsigned int count) {
			m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
			m_Stride += sizeof(GLuint)* count;
		}
		template<>
		void Push<unsigned char>(unsigned int count) {
			m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
			m_Stride += sizeof(GLbyte) * count;
		}
		inline unsigned int GetStride() const { return m_Stride; }
		inline const std::vector<VertexBufferElement>& GetElements() const { return  m_Elements; }
	};
}
#endif