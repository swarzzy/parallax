#include "UniformBuffer.h"
#include "../shading/Shader.h"
#include "VertexBuffer.h"

namespace prx::API {
	UniformBuffer::UniformBuffer(const std::shared_ptr<Shader>& attachedShader, uint bindingPoint, std::string_view ubName, BufferType type)
		: m_BufferHandle(0)
		, m_Size(0)
		, m_BindingPoint(bindingPoint)
		, m_UniformBlockIndex(0)
		, m_UBName(ubName)
		, m_AttachedShader(attachedShader)
		, m_Type(type)
	{
		m_AttachedShader->bind();
		GLCall(m_UniformBlockIndex = glGetUniformBlockIndex(m_AttachedShader->getID(), m_UBName.c_str()));

		// Checking if we get valid index
		if (m_UniformBlockIndex == GL_INVALID_INDEX)
			PRX_FATAL("API::UNIFORM BUFFER: Failed to get uniform block index.");
		// Checking for maximum binding point
		int maxBindings;
		GLCall(glGetIntegerv(GL_MAX_VERTEX_UNIFORM_BLOCKS, &maxBindings));
		if (static_cast<int>(m_BindingPoint) >= maxBindings)
			PRX_FATAL("API::UNIFORM BUFFER: Maximum allowed number of binding points exceeded.");

		GLCall(glUniformBlockBinding(m_AttachedShader->getID(), m_UniformBlockIndex, m_BindingPoint));

		GLCall(glGenBuffers(1, &m_BufferHandle));

		m_AttachedShader->unbind();
	}

	UniformBuffer::~UniformBuffer() {
		GLCall(glDeleteBuffers(1, &m_BufferHandle));
	}

	void UniformBuffer::bind() {
		glBindBuffer(GL_UNIFORM_BUFFER, m_BufferHandle);
	}

	void UniformBuffer::unbind() {
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void UniformBuffer::resize(size_t size) {
		m_Size = size;
		GLCall(glBindBuffer(GL_UNIFORM_BUFFER, m_BufferHandle));
		GLCall(glBufferData(GL_UNIFORM_BUFFER, size, nullptr, VertexBuffer::getGLBufferType(m_Type)));
		GLCall(glBindBuffer(GL_UNIFORM_BUFFER, 0));

		GLCall(glBindBufferBase(GL_UNIFORM_BUFFER, m_BindingPoint, m_BufferHandle));
	}

	void UniformBuffer::setData(size_t size, const void* data) {
		if (size > m_Size) {
			PRX_ERROR("API:UNIFORM BUFFER: The data size is larger than buffer size.\n-> DATA SIZE: ", size,
						"\n-> BUFFER SIZE:", m_Size);
		}
		GLCall(glBindBuffer(GL_UNIFORM_BUFFER, m_BufferHandle));
		GLCall(glBufferSubData(GL_UNIFORM_BUFFER, 0, size, data));
		GLCall(glBindBuffer(GL_UNIFORM_BUFFER, 0));
	}

	void* UniformBuffer::getPointer() {
		void* pointer;
		GLCall(pointer = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY));
		return pointer;
	}

	void UniformBuffer::releasePointer() {
		GLCall(glUnmapBuffer(GL_UNIFORM_BUFFER));
	}
}