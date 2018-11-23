#include "Texture.h"
#include "../utils/error_handling/GLErrorHandler.h"
#include "../resources/ImageLoader.h"

namespace prx {

	Texture::Texture(std::string_view path) 
		: TextureBase(path),
		  m_Pixels(nullptr),
		  m_PixelsWidth(0),
		  m_PixelsHeight(0),
		  m_PixelsFormat(TextureFormat::RED),
		  m_FromBitmap(false)
	{}

	Texture::Texture(byte* data, unsigned int width, unsigned int height, TextureFormat format)
		// Textures from bitmap now incompatible with resource manager
		: TextureBase(),
		  m_Pixels(nullptr),
		  m_PixelsWidth(width),
		  m_PixelsHeight(height),
		  m_PixelsFormat(format),
		  m_FromBitmap(true)
	{
		unsigned storageSize = m_PixelsWidth * m_PixelsHeight * TextureBase::getFormatDepth(m_PixelsFormat);
		m_Pixels = new byte[storageSize];
		memcpy(m_Pixels, data, storageSize * sizeof(byte));
	}

	
	Texture::Texture(unsigned width, unsigned height, TextureFormat format) 
		: TextureBase(),
		m_Pixels(nullptr),
		m_PixelsWidth(width),
		m_PixelsHeight(height),
		m_PixelsFormat(format),
		m_FromBitmap(true)
	{}
	

	Texture::~Texture() {
		unload();
		delete m_Pixels;
	}

	void Texture::initInternal() {
		if (m_FromBitmap) {
			if (m_Pixels != nullptr)
				loadFromBitmap(m_Pixels, m_PixelsWidth, m_PixelsHeight, m_PixelsFormat);
			else
				loadEmpty(m_PixelsWidth, m_PixelsHeight, m_PixelsFormat);
		} else
			loadFromFile();
	}

	void Texture::destroyInternal() {
			GLCall(glDeleteTextures(1, &m_TexID));
			m_TexID = 0;
			m_Width = 0;
			m_Height = 0;
			m_Format = TextureFormat::RED;
	}
}
