#pragma once
// ================================
// Parallax Engine framebuffer v1.0
// ================================
//
// LOOK CPP FILE FOR DOCUMENTATION
//

#include "../Common.h"

#include <hypermath.h>

#include <vector>
#include <array>

namespace prx {
	// Forward declarations
	class Texture;

	enum class DepthStencilType {
		TEXTURE,
		RENDERBUFFER
	};

	enum class DepthStencilFormat {
		DEPTH_ONLY,
		DEPTH24_STENCIL8,
	};

	class FrameBuffer final {
		PRX_DISALLOW_COPY_AND_MOVE(FrameBuffer)
	private:
		static const unsigned MAX_COLOR_ATTACHMENTS = 8; // Minimum number of attachments according to OpenGL specification

		struct ColorAttachmentStatus {
			unsigned colorAttachment;
			bool status;
		};

		DepthStencilType	m_DepthStencilType;
		DepthStencilFormat	m_DepthStencilFormat;
		unsigned			m_FrameBufferHandle;
		unsigned			m_DepthStencilBufferHandle;
		unsigned			m_Width;
		unsigned			m_Height;
		hpm::vec4			m_ClearColor;

		std::vector<std::shared_ptr<Texture>>	m_RenderTargets;
		std::shared_ptr<Texture>				m_DepthStencilTarget;

		std::array<ColorAttachmentStatus, MAX_COLOR_ATTACHMENTS> m_ColorAttachmentsStatuses;

	public:
		FrameBuffer(unsigned width, unsigned height, DepthStencilType type, DepthStencilFormat format);
		~FrameBuffer();
		
		bool validate(); // Framebuffer should be bound before call this method

		unsigned getWidth() const;
		unsigned getHeight() const;

		std::shared_ptr<Texture> getColorAttachment(unsigned attachmentNumber) const;
		std::shared_ptr<Texture> getDepthStencilAttachment() const;

		bool hasDepth() const;
		bool hasStencil() const;

		void init();

		void bind();
		void unbind();
		void clear(); // ! Changes global clear color setting

		void setClearColor(unsigned color);

		void attachColorTexture(std::shared_ptr<Texture>& texture, unsigned attachmentNumber);
		void attachDepthStencilTexture(std::shared_ptr<Texture>& texture);

		void deattachColorTexture(unsigned attachmentNumber);
		void deattachDepthStencilTexture();

		static unsigned maxColorAttachments();
	};
}