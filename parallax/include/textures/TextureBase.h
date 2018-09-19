#pragma once
#ifndef _PARALLAX_TEXTURES_TEXTURE_BASE_H_
#define _PARALLAX_TEXTURES_TEXTURE_BASE_H_

#include "../../ext/GL/glew.h"

namespace prx {

	enum class TextureFormat {
		RED, RGB, RGBA
	};

	class TextureBase {
	protected:
		unsigned int  m_TexID;
		unsigned int  m_Width;
		unsigned int  m_Height;
		TextureFormat m_Format;
	
	public:
		
		virtual ~TextureBase() {};

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		inline unsigned int  getID()	 const { return m_TexID; } 
		inline unsigned int  getWidth()	 const { return m_Width; }
		inline unsigned int  getHeight() const { return m_Height;}
	
	public:
		static GLenum getGLFormat(TextureFormat format) {
			switch (format) {
			case TextureFormat::RED:  return GL_RED;
			case TextureFormat::RGB:  return GL_RGB;
			case TextureFormat::RGBA: return GL_RGBA;
			default: return 0;
			}
		}
	};

}
#endif
