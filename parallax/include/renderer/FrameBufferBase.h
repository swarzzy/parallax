#pragma once
#ifndef _PARALLAX_RENDERER_FRAMEBUFFERBASE_H_
#define _PARALLAX_RENDERER_FRAMEBUFFERBASE_H_
#include "../utils/error_handling/GLErrorHandler.h"

namespace prx {

	constexpr unsigned int PARALLAX_DEFAULT_FRAMEBUFFER = 0;

	class FrameBufferBase {
	protected:
		unsigned int m_ID;
		unsigned int m_Width;
		unsigned int m_Height;

		FrameBufferBase(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {};

	public:
		virtual ~FrameBufferBase() {};

		virtual void bind()   const { GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_ID)); };
		virtual void unbind() const { GLCall(glBindFramebuffer(GL_FRAMEBUFFER, PARALLAX_DEFAULT_FRAMEBUFFER)); };

		virtual void clear() = 0;
		virtual bool validate() = 0;

		inline constexpr unsigned int getWidth()  const { return m_Width;	}
		inline constexpr unsigned int getHeight() const { return m_Height;	}
		inline constexpr unsigned int getID()	  const { return m_ID;		}
	
	protected:
		FrameBufferBase(const FrameBufferBase& other) = delete;
		FrameBufferBase& operator=(const FrameBufferBase& other) = delete;
		FrameBufferBase& operator=(FrameBufferBase&& other) = delete;
		FrameBufferBase& operator=(const FrameBufferBase&& other) = delete;

	};
}
#endif