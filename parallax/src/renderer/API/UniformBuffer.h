#pragma once

#include "../../Common.h"
#include <string>

namespace prx {
	// Defined in VertexBuffer.h
	// TODO: move to API namespace
	enum class BufferType;
	class Shader;
}

namespace prx::API {
	
	class UniformBuffer final {
		PRX_DISALLOW_COPY_AND_MOVE(UniformBuffer)
	private:
		uint					m_BufferHandle;
		size_t					m_Size;
		uint					m_BindingPoint;
		uint					m_UniformBlockIndex;
		std::string				m_UBName;
		std::shared_ptr<Shader> m_AttachedShader;
		BufferType				m_Type;

	public:
		UniformBuffer(const std::shared_ptr<Shader>& attachedShader, uint bindingPoint, std::string_view ubName, BufferType type);
		~UniformBuffer();

		void bind();
		void unbind();

		void resize(size_t size);

		void setData(size_t size, const void* data);

		// TODO: pointer access
		void* getPointer();
		void releasePointer();
	};
}