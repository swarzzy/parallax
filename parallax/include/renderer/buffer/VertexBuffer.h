#pragma once
#ifndef _VERTEXBUFFER_H_
#define _VERTEXBUFFER_H_

namespace prx {

	class VertexBuffer {
	private:
		unsigned int m_RendererID;
	public:
		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;
	};
}

#endif