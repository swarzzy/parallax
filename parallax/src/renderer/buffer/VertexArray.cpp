#include "VertexArray.h"

#include "../../utils/error_handling/GLErrorHandler.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#pragma warning(push)
#pragma warning(disable:4312)
namespace prx {

	VertexArray::VertexArray() {
		GLCall(glGenVertexArrays(1, &m_RendererID));
	}

	VertexArray::~VertexArray() {
		GLCall(glDeleteVertexArrays(1, &m_RendererID));
	}

	void VertexArray::AddBuffer(const VertexBuffer & vb, const VertexBufferLayout & layout, const IndexBuffer& ib) {
		Bind();
		vb.Bind();
		ib.Bind();
		const auto& elements = layout.GetElements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++) {
			GLCall(glEnableVertexAttribArray(i));
			GLCall(glVertexAttribPointer(i, elements[i].count, elements[i].type, elements[i].normalized
				, layout.GetStride(), reinterpret_cast<void*>(offset)));
			offset += elements[i].count * VertexBufferElement::GetSizeOfType(elements[i].type);
		}
		Unbind();
	}

	void VertexArray::AddBuffer(const VertexBuffer & vb, const VertexBufferLayout & layout) {
		Bind();
		vb.Bind();
		const auto& elements = layout.GetElements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++) {
			GLCall(glEnableVertexAttribArray(i));
			GLCall(glVertexAttribPointer(i, elements[i].count, elements[i].type, elements[i].normalized
				, layout.GetStride(), reinterpret_cast<void*>(offset)));
			offset += elements[i].count * VertexBufferElement::GetSizeOfType(elements[i].type);
		}
		Unbind();
	}

	void VertexArray::Bind() const {
		GLCall(glBindVertexArray(m_RendererID));
	}

	void VertexArray::Unbind() const {
		GLCall(glBindVertexArray(0));
	}
}
#pragma warning(pop)