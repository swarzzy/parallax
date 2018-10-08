#include <renderer/FrameBuffer2D.h>

namespace prx {
	FrameBuffer2D::FrameBuffer2D(unsigned int width, unsigned int height)
		: FrameBufferBase(width, height), 
		  m_Texture(new Texture(nullptr, width, height, TextureFormat::RGB)),
		  m_Valid(true)
	{
		init();
	}

	FrameBuffer2D::FrameBuffer2D(FrameBuffer2D&& other)
		:FrameBufferBase(other.getWidth(), other.getHeight()), 
		 m_Texture(other.m_Texture), 
		 m_RBO(other.m_RBO),
		 m_Valid(true)
	{
		m_ID = other.m_ID;

		other.m_RBO		= 0;
		other.m_Texture = nullptr;
		other.m_ID		= 0;
		other.m_Height	= 0;
		other.m_Width	= 0;
		other.m_Valid	= false;
	}

	bool FrameBuffer2D::operator==(const FrameBuffer2D& other) {
		// Just checking them by OpenGL ID
		return this->getID() == other.getID();
	}

	bool FrameBuffer2D::operator!=(const FrameBuffer2D& other) {
		// Just checking them by OpenGL ID
		return this->getID() != other.getID();
	}

	FrameBuffer2D::~FrameBuffer2D() {
		GLCall(glDeleteFramebuffers(1, &m_ID));
		GLCall(glDeleteRenderbuffers(1, &m_RBO));
		delete m_Texture;
	}

	void FrameBuffer2D::clear() {
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

	bool FrameBuffer2D::validate() {
		bind();
		bool result = (GLCall(glCheckFramebufferStatus(GL_FRAMEBUFFER)) == GL_FRAMEBUFFER_COMPLETE) && m_Valid;
		unbind();
		return result;
	}

	void FrameBuffer2D::init() {
		GLCall(glGenFramebuffers(1, &m_ID));
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_ID));
		
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER,
									  GL_COLOR_ATTACHMENT0,
									  GL_TEXTURE_2D,
									  m_Texture->getID(),
									  0));

		GLCall(glGenRenderbuffers(1, &m_RBO));
		GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_RBO));
		GLCall(glRenderbufferStorage(GL_RENDERBUFFER,
									 GL_DEPTH,
									 m_Width,
									 m_Height));
		GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));

		GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER,
										 GL_DEPTH,
										 GL_RENDERBUFFER,
										 m_RBO));

		if (GLCall(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)) 
			PRX_WARN("(RENDERBUFFER): Renderbuffer validation failed\n-> API ID: ", m_ID);

		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, PARALLAX_DEFAULT_FRAMEBUFFER));
	}
}
