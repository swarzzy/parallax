// *******************************************
// Parallax Engine framebuffer v1.0
// *******************************************
//
// ===========================
// REQUIRED OPENGL API VERSION
// ===========================
// Required OpenGL version: 3
// Required OpenGL ES version: 3
//
// ===========================================
// CODE SECTIONS (search for them to navigate)
// ===========================================
//
// [SECTION] FRAMEBUFFER CONSTRUCTOR
// [SECTION] FRAMEBUFFER DESTRUCTOR
// [SECTION] FRAMEBUFFER VALIDATE
// [SECTION] FRAMEBUFFER GETTERS
// [SECTION] FRAMEBUFFER INIT
// [SECTION] FRAMEBUFFER BIND
// [SECTION] FRAMEBUFFER UNBIND
// [SECTION] FRAMEBUFFER CLEARING METHODS
// [SECTION] FRAMEBUFFER ATTACHMENT METHODS
// [SECTION] FRAMEBUFFER DEATTACHMENT METHODS
// [SECTION] FRAMEBUFFER MAX COLOR ATTACHMENTS
//
// ====================
// API BREAKING CHANGES
// ====================
// Major changes that breaks whole API and some client code need to be changed
//
// 2018-11-16:	Initial work. Create this class
//
// =====
// TODO:
// =====
// -- Framebuffer without depth and stencil targets
// -- Depth and stencil in different targets and stencil only
//

#include "FrameBuffer.h"

#include "../textures/Texture.h"
#include "../scene/Director.h"

namespace prx {
//-----------------------------------------------------------------------------
// [SECTION] FRAMEBUFFER CONSTRUCTOR
//-----------------------------------------------------------------------------
	FrameBuffer::FrameBuffer(unsigned width, unsigned height, DepthStencilType type, DepthStencilFormat format)
		: m_DepthStencilType(type)
		, m_DepthStencilFormat(format)
		, m_FrameBufferHandle(0)
		, m_Width(width)
		, m_Height(height)
		, m_ClearColor(hpm::vec4(0.0, 0.0, 0.0, 1.0))
		, m_DepthStencilTarget(nullptr)
	{
		m_RenderTargets.reserve(MAX_COLOR_ATTACHMENTS);
		for (unsigned i = 0; i < MAX_COLOR_ATTACHMENTS; i++)
			m_RenderTargets.emplace_back(nullptr);

		for (unsigned i = 0; i < MAX_COLOR_ATTACHMENTS; i++) {
			m_ColorAttachmentsStatuses[i].colorAttachment = GL_COLOR_ATTACHMENT0 + i;
			m_ColorAttachmentsStatuses[i].status = false;
		}
	}

//-----------------------------------------------------------------------------
// [SECTION] FRAMEBUFFER DESTRUCTOR
//-----------------------------------------------------------------------------

	FrameBuffer::~FrameBuffer() {
		GLCall(glDeleteFramebuffers(1, &m_FrameBufferHandle));
		if (m_DepthStencilBufferHandle != 0) {
			GLCall(glDeleteRenderbuffers(1, &m_DepthStencilBufferHandle));
		}
		if (m_DepthStencilTarget != nullptr)
			m_DepthStencilTarget->destroy();
		for (auto& target : m_RenderTargets)
			if (target != nullptr)
				target->destroy();
	}

//-----------------------------------------------------------------------------
// [SECTION] FRAMEBUFFER VALIDATE
//-----------------------------------------------------------------------------

	bool FrameBuffer::validate() {
		if (m_FrameBufferHandle == 0) {
			PRX_WARN("FRAMEBUFFER: Framebuffer is not initialized.");
			return false;
		}
		GLCall(auto result = glCheckFramebufferStatus(GL_FRAMEBUFFER));
		if (result == GL_FRAMEBUFFER_COMPLETE)
			return true;
		return false;
	}

//-----------------------------------------------------------------------------
// [SECTION] FRAMEBUFFER GETTERS
//-----------------------------------------------------------------------------

	unsigned FrameBuffer::getWidth() const {
		return m_Width;
	}

	unsigned FrameBuffer::getHeight() const {
		return m_Height;
	}

	std::shared_ptr<Texture> FrameBuffer::getColorAttachment(unsigned attachmentNumber) const {
		if (m_FrameBufferHandle == 0) {
			PRX_ERROR("FRAMEBUFFER: Framebuffer is not initialized.");
			return nullptr;
		}

		if (attachmentNumber >= MAX_COLOR_ATTACHMENTS) {
#ifdef PARALLAX_DEBUG
			PRX_WARN("FRAMEBUFFER: Wrong attachment slot\n-> SLOT: ", attachmentNumber);
#endif
			return nullptr;
		}

		if (m_ColorAttachmentsStatuses[attachmentNumber].status == false) {
#ifdef PARALLAX_DEBUG
			PRX_WARN("FRAMEBUFFER: Empty attachment slot\n-> SLOT: ", attachmentNumber);
#endif
			return nullptr;
		}
		return m_RenderTargets[attachmentNumber];
	}

	std::shared_ptr<Texture> FrameBuffer::getDepthStencilAttachment() const {
		if (m_FrameBufferHandle == 0) {
			PRX_ERROR("FRAMEBUFFER: Framebuffer is not initialized.");
			return nullptr;
		}

		if (m_DepthStencilType != DepthStencilType::TEXTURE) {
			PRX_WARN("FRAMEBUFFER: Falied to get depth-stencil texture. Framebuffer has renderbuffer depth and stencil format.");
			return nullptr;
		}

		if (m_DepthStencilTarget == nullptr) {
#ifdef PARALLAX_DEBUG
			PRX_WARN("FRAMEBUFFER: Framebuffer has no depth-stencil attachment.");
#endif
			return nullptr;
		}

		return  m_DepthStencilTarget;
	}

	bool FrameBuffer::hasDepth() const {
		return m_DepthStencilFormat == DepthStencilFormat::DEPTH24_STENCIL8 || m_DepthStencilFormat == DepthStencilFormat::DEPTH_ONLY;
	}

	bool FrameBuffer::hasStencil() const {
		return m_DepthStencilFormat == DepthStencilFormat::DEPTH24_STENCIL8;
	}

//-----------------------------------------------------------------------------
// [SECTION] FRAMEBUFFER INIT
//-----------------------------------------------------------------------------

	void FrameBuffer::init() {
		if (m_FrameBufferHandle != 0) {
			PRX_WARN("FRAMEBUFFER: Framebuffer already initialized.");
			return;
		}

		int maxFrameBufferSize;
		GLCall(glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &maxFrameBufferSize));
		if (m_Width > static_cast<unsigned>(maxFrameBufferSize) || m_Height > static_cast<unsigned>(maxFrameBufferSize))
			PRX_ERROR("FRAMEBUFFER: Maximum allowed OpenGL framebuffer size exceeded.\n-> MAX OPENGL FRAMEBUFFER SIZE: ", maxFrameBufferSize);

		GLCall(glGenFramebuffers(1, &m_FrameBufferHandle));
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferHandle));

		// Setting depth and stencil buffers if they are renderbuffers
		if (m_DepthStencilType == DepthStencilType::RENDERBUFFER) {
			// Depth Only
			if (m_DepthStencilFormat == DepthStencilFormat::DEPTH_ONLY) {
				GLCall(glGenRenderbuffers(1, &m_DepthStencilBufferHandle));
				GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_DepthStencilBufferHandle));
				GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, m_Width, m_Height));
				GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthStencilBufferHandle));
				GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
			}
			// Depth24 Stencil8
			else if (m_DepthStencilFormat == DepthStencilFormat::DEPTH24_STENCIL8) {
				GLCall(glGenRenderbuffers(1, &m_DepthStencilBufferHandle));
				GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_DepthStencilBufferHandle));
				GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height));
				GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_DepthStencilBufferHandle));
				GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
			}
		}

		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

//-----------------------------------------------------------------------------
// [SECTION] FRAMEBUFFER BIND
//-----------------------------------------------------------------------------

	void FrameBuffer::bind() {
		if (m_FrameBufferHandle == 0) {
			PRX_ERROR("FRAMEBUFFER: Framebuffer is not initialized.");
			return;
		}
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferHandle));

#ifdef PARALLAX_DEBUG
		if (!validate()) {
			PRX_ERROR("FRAMEBUFFER: Framebuffer is incomplete");
			GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
			return;
		}

		// Checking viewport
		auto viewport = Director::getInstance()->getViewport();
		if (viewport.x != m_Width || viewport.y != m_Height)
			PRX_WARN("FRAMEBUFFER: Framebuffer and viewport have different sizes.\n-> FRAMEBUFFER SIZE: ", m_Width, " x ", m_Height,
					"\n-> VIEWPORT SIZE: ", viewport.x, " x ", viewport.y);
#endif
		unsigned colorAttachments[MAX_COLOR_ATTACHMENTS];
		// NOTE: It Might be slow to go through all available attachments at every binding.
		// Possible solution is make attachments as stack with push colorAttachment and pop methods.
		for (unsigned i = 0; i < MAX_COLOR_ATTACHMENTS; i++) {
			auto& attachment = m_ColorAttachmentsStatuses[i];
			if (attachment.status == true)
				colorAttachments[i] = attachment.colorAttachment;
			else
				colorAttachments[i] = GL_NONE;
		}
		GLCall(glDrawBuffers(MAX_COLOR_ATTACHMENTS, colorAttachments));
	}

//-----------------------------------------------------------------------------
// [SECTION] FRAMEBUFFER UNBIND
//-----------------------------------------------------------------------------

	void FrameBuffer::unbind() {
		if (m_FrameBufferHandle == 0) {
			PRX_ERROR("FRAMEBUFFER: Framebuffer is not initialized.");
			return;
		}
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

//-----------------------------------------------------------------------------
// [SECTION] FRAMEBUFFER CLEARING METHODS
//-----------------------------------------------------------------------------

	void FrameBuffer::clear() {
		GLCall(glClearColor(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a));
		if (hasStencil()) {
			GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
		}
		else {
			GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		}
	}

	void FrameBuffer::setClearColor(unsigned color) {
		auto mask = static_cast<unsigned int>(0x000000ff);

		float r = (color & mask) / 255.0f;
		float g = ((color >> 8)  & mask) / 255.0f;
		float b = ((color >> 16) & mask) / 255.0f;
		float a = ((color >> 24) & mask) / 255.0f;

		m_ClearColor = hpm::vec4(r, g, b, a);
	}

//-----------------------------------------------------------------------------
// [SECTION] FRAMEBUFFER ATTACHMENT METHODS
//-----------------------------------------------------------------------------

	void FrameBuffer::attachColorTexture(std::shared_ptr<Texture>& texture, unsigned attachmentNumber) {
		if (m_FrameBufferHandle == 0) {
			PRX_ERROR("FRAMEBUFFER: Framebuffer is not initialized.");
			return;
		}

		if (attachmentNumber >= MAX_COLOR_ATTACHMENTS) {
			PRX_ERROR("FRAMEBUFFER: Failed to attach color texture. Wrond attachment number.\n-> ATT. NUMBER: ", attachmentNumber);
			return;
		}

		texture->init(); // TODO: get rid of this stupid initialization
		if (texture->getWidth() != m_Width || texture->getHeight() != m_Height) {
			PRX_ERROR("FRAMEBUFFER: Failed to attach color texture. Wrong texture size.\n-> TEXTURE SIZE: ", texture->getWidth(), " x ", texture->getHeight(),
						"\n-> FRAMEBUFFER SIZE: ", m_Width, " x ", m_Height);
			texture->destroy();
			return;
		}

		// Free previous attachment
		if (m_RenderTargets[attachmentNumber] != nullptr) {
			m_RenderTargets[attachmentNumber]->destroy();
		}
		// Setting new attachment
		m_RenderTargets[attachmentNumber] = texture;
		m_ColorAttachmentsStatuses[attachmentNumber].status = true;
		
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferHandle));
		
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachmentNumber, GL_TEXTURE_2D, texture->getID(), 0));
		// TODO: validate framebuffer

		GLCall(glBindFramebuffer(GL_FRAMEBUFFER,0));
	}

	void FrameBuffer::attachDepthStencilTexture(std::shared_ptr<Texture>& texture) {
		if (m_FrameBufferHandle == 0) {
			PRX_ERROR("FRAMEBUFFER: Framebuffer is not initialized.");
			return;
		}

		if (m_DepthStencilType == DepthStencilType::RENDERBUFFER) {
			PRX_ERROR("FRAMEBUFFER: Can not attach depth or stencil texture to a framebuffer with renderbuffer depth-stencil target type");
			return;
		}
		texture->init(); // TODO: get rid of this stupid initialization
		// Checking texture size
		if (m_Width != texture->getWidth() || m_Height != texture->getHeight()) {
			PRX_ERROR("FRAMEBUFFER: Failde to attach depth of stencil texture. Wrong texture size.\n-> TEXTURE SIZE: ", texture->getWidth(), " x ", texture->getHeight(),
				"\n-> FRAMEBUFFER SIZE: ", m_Width, " x ", m_Height);
			texture->destroy();
			return;
		}

		// If DEPTH_ONLY format
		if (m_DepthStencilFormat == DepthStencilFormat::DEPTH_ONLY) {
			if (texture->getFormat() != TextureFormat::DEPTH) {
				// TODO: toString for FrameBuffer formats and texture types
				PRX_ERROR("FRAMEBUFFER: Failed to attach depth of stencil texture. Wrong texture type.\n->TEXTURE TYPE: Not depth only \n->FRAMEBUFFER TYPE: DEPTH_ONLY");
				texture->destroy();
				return;
			}

			// Free previous attachment
			if (m_DepthStencilTarget != nullptr) {
				m_DepthStencilTarget->destroy();
			}
			// Setting new attachment
			m_DepthStencilTarget = texture;

			GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferHandle));
			GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture->getID(), 0));
			GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		}
		// If DEPTH24_STENCIL8 format
		else if (m_DepthStencilFormat == DepthStencilFormat::DEPTH24_STENCIL8) {
			if (texture->getFormat() != TextureFormat::DEPTH_STENCIL) {
				// TODO: toString for FrameBuffer formats and texture types
				PRX_ERROR("FRAMEBUFFER: Failed to attach depth of stencil texture. Wrong texture type.\n->TEXTURE TYPE: Not depth only \n->FRAMEBUFFER TYPE: DEPTH_ONLY");
				texture->destroy();
				return;
			}

			// Free previous attachment
			if (m_DepthStencilTarget != nullptr) {
				m_DepthStencilTarget->destroy();
			}
			// Setting new attachment
			m_DepthStencilTarget = texture;

			GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferHandle));
			GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture->getID(), 0));
			GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		}
		// TODO: validate framebuffer?
	}

//-----------------------------------------------------------------------------
// [SECTION] FRAMEBUFFER DEATTACHMENT METHODS
//-----------------------------------------------------------------------------

	void FrameBuffer::deattachColorTexture(unsigned attachmentNumber) {
		if (m_FrameBufferHandle == 0) {
			PRX_WARN("FRAMEBUFFER: Framebuffer is not initialized.");
			return;
		}

		if (attachmentNumber >= MAX_COLOR_ATTACHMENTS) {
			PRX_ERROR("FRAMEBUFFER: Failed to deattach color texture. Wrond attachment number.\n-> ATT. NUMBER: ", attachmentNumber);
			return;
		}

		if (m_ColorAttachmentsStatuses[attachmentNumber].status == false) {
			PRX_WARN("FRAMEBUFFER: Nothing to deattach.\n-> ATTACHMENT NUMBER: ", attachmentNumber);
			return;
		}

		m_RenderTargets[attachmentNumber]->destroy();
		m_RenderTargets[attachmentNumber] = nullptr;
		m_ColorAttachmentsStatuses[attachmentNumber].status = false;

		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferHandle));

		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachmentNumber, GL_TEXTURE_2D, 0, 0));

		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	void FrameBuffer::deattachDepthStencilTexture() {
		if (m_FrameBufferHandle == 0) {
			PRX_ERROR("FRAMEBUFFER: Framebuffer is not initialized.");
			return;
		}

		if (m_DepthStencilType == DepthStencilType::RENDERBUFFER) {
			PRX_ERROR("FRAMEBUFFER: Can not deattach depth or stencil texture to a framebuffer with renderbuffer depth-stencil target type");
			return;
		}

		// If DEPTH_ONLY format
		if (m_DepthStencilFormat == DepthStencilFormat::DEPTH_ONLY) {
			if (m_DepthStencilTarget == nullptr) {
				PRX_WARN("FRAMEBUFFER: Nothing to deattach.");
				return;
			}

			m_DepthStencilTarget->destroy();
			m_DepthStencilTarget = nullptr;

			GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferHandle));
			GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 0, 0));
			GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		}
		// If DEPTH24_STENCIL8 format
		else if (m_DepthStencilFormat == DepthStencilFormat::DEPTH24_STENCIL8) {
			if (m_DepthStencilTarget == nullptr) {
				PRX_WARN("FRAMEBUFFER: Nothing to deattach.");
				return;
			}

			m_DepthStencilTarget->destroy();
			m_DepthStencilTarget = nullptr;

			GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferHandle));
			GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, 0, 0));
			GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		}
	}

//-----------------------------------------------------------------------------
// [SECTION] FRAMEBUFFER MAX COLOR ATTACHMENTS
//-----------------------------------------------------------------------------

	unsigned FrameBuffer::maxColorAttachments() {
		return MAX_COLOR_ATTACHMENTS;
	}
}