#pragma once
#ifndef _PARALLAX_TEXTURES_TEXTURE_BASE_H_
#define _PARALLAX_TEXTURES_TEXTURE_BASE_H_

#include "../ext/GL/glew.h"
#include "../utils/error_handling/GLErrorHandler.h"
#include "../resources/Resource.h"
#include "../utils/SimpleHash.h"

namespace prx {

	enum class TextureFormat {
		RED, RGB, RGBA
	};

	class TextureBase : public Resource {
	public:
		inline static const float DEFAULT_UV[8] = {
			0.0f, 0.0f,	0.0f, 1.0f,	1.0f, 1.0f,	1.0f, 0.0f
		};
		inline static const float DEFAULT_REFLECT_UV[8] = {
			1.0f, 0.0f, 1.0f, 1.0f,	0.0f, 1.0f,	0.0f, 0.0f
		};

	protected:
		unsigned int  m_TexID;
		unsigned int  m_Width;
		unsigned int  m_Height;
		TextureFormat m_Format;

		TextureBase(std::string_view name = "unnamed", std::string_view filepath = "unknown") 
			: Resource(name, filepath, hash_string(name)) 
		{};

	public:
		
		virtual ~TextureBase() {};

		inline virtual void bind()	 const { GLCall(glBindTexture(GL_TEXTURE_2D, m_TexID)); };
		inline virtual void unbind() const { GLCall(glBindTexture(GL_TEXTURE_2D, 0)); };

		inline unsigned int  getID()	 const { return m_TexID;  } 
		inline unsigned int  getWidth()	 const { return m_Width;  }
		inline unsigned int  getHeight() const { return m_Height; }
		inline TextureFormat getFormat() const { return m_Format; }
	
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
