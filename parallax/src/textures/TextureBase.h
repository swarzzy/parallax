#pragma once
#ifndef _PARALLAX_TEXTURES_TEXTURE_BASE_H_
#define _PARALLAX_TEXTURES_TEXTURE_BASE_H_

#include "../Common.h"
#include "../ext/GL/glew.h"
#include "../utils/error_handling/GLErrorHandler.h"
#include "../resources/Resource.h"

namespace prx {

	enum class TextureFormat {
		RED, RGB, RGBA
	};

	enum class TextureWrap {
		CLAMP_TO_EDGE			= GL_CLAMP_TO_EDGE,
		CLAMP_TO_BORDER			= GL_CLAMP_TO_BORDER,
		MIRRORED_REPEAT			= GL_MIRRORED_REPEAT,
		REPEAT					= GL_REPEAT,
		MIRROR_CLAMP_TO_EDGE	= GL_MIRROR_CLAMP_TO_EDGE
	};

	enum class TextureFilter {
		NEAREST = GL_NEAREST,
		LINEAR	= GL_LINEAR
	};

	class TextureBase : public Resource {
		PRX_DISALLOW_COPY_AND_MOVE(TextureBase)

	protected:
		static const unsigned int UV_ARRAY_SIZE;

		static const float DEFAULT_UV[8];
		static const float DEFAULT_REFLECT_UV[8];

		static const TextureWrap DEFAULT_TEXTURE_WRAP;
		static const TextureFilter DEFAULT_TEXTURE_FILTER;

		static const byte EMPTY_TEXTURE_COLOR;


		unsigned int  m_TexID;
		unsigned int  m_Width;
		unsigned int  m_Height;
		TextureFormat m_Format;
		TextureWrap	  m_WrapMode;
		TextureFilter m_FilterMode;

		explicit TextureBase(std::string_view filepath);
		TextureBase();

	public:
		virtual ~TextureBase() {};

		inline virtual void bind()	 const noexcept { GLCall(glBindTexture(GL_TEXTURE_2D, m_TexID)); };
		inline virtual void unbind() const noexcept { GLCall(glBindTexture(GL_TEXTURE_2D, 0)); };

		inline unsigned int  getID()	 const noexcept { return m_TexID;  } 
		inline unsigned int  getWidth()	 const noexcept { return m_Width;  }
		inline unsigned int  getHeight() const noexcept { return m_Height; }
		inline TextureFormat getFormat() const noexcept { return m_Format; }

		void setParameters(TextureWrap wrapMode, TextureFilter filterMode);

	protected:
		void loadFromBitmap(byte* pixels, unsigned width, unsigned height, TextureFormat format);
		void loadFromFile();
		void loadEmpty(unsigned width, unsigned height, TextureFormat format);
		void unload();

		void updateParameters();

	public:
		static unsigned getGLFormat(TextureFormat format);
		static unsigned getFormatDepth(TextureFormat format);

		inline static const float* defaultUV() noexcept { return DEFAULT_UV; }
		inline static const float* reflectDefaultUV() noexcept { return DEFAULT_REFLECT_UV; }
		inline static const TextureWrap defaultTextureWrap() noexcept { return DEFAULT_TEXTURE_WRAP; }
		inline static const TextureFilter defaultTextureFilter() noexcept { return DEFAULT_TEXTURE_FILTER; }
	};
}
#endif