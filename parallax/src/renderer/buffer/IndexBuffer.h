#pragma once
#ifndef _PARALLAX_RENDERER_BUFFER_INDEXBUFFER_H_
#define _PARALLAX_RENDERER_BUFFER_INDEXBUFFER_H_

namespace prx {

	class IndexBuffer {
	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
	public:
		IndexBuffer(const unsigned int* data, unsigned int count);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;
		inline unsigned int GetCount() const { return m_Count; };
	};
}

#endif
