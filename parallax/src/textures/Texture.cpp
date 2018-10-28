#include <textures/Texture.h>
#include <utils/error_handling/GLErrorHandler.h>
#include <resources/ImageLoader.h>

namespace prx {

	Texture::Texture(std::string_view name, std::string_view path) 
		: TextureBase(name, path),
		  m_Pixels(nullptr),
		  m_PixelsWidth(0),
		  m_PixelsHeight(0),
		  m_PixelsFormat(TextureFormat::RED) {
		//init();
	}

	Texture::Texture(byte* data, unsigned int width, unsigned int height, TextureFormat format)
		// Textures from bitmap now incompatible with resource manager
		: TextureBase(),
		  m_Pixels(nullptr),
		  m_PixelsWidth(width),
		  m_PixelsHeight(height),
		  m_PixelsFormat(format)
	{
		unsigned storageSize = m_PixelsWidth * m_PixelsHeight * TextureBase::getFormatDepth(m_PixelsFormat);
		m_Pixels = new byte[storageSize];
		memcpy(m_Pixels, data, storageSize * sizeof(byte));
		 //init();
	}

	Texture::~Texture() {
		unload();
		delete m_Pixels;
	}

	void Texture::init() {
		GLCall(glGenTextures(1, &m_TexID));

		updateParameters();

		GLCall(glBindTexture(GL_TEXTURE_2D, m_TexID));

		if (m_Pixels != nullptr)
			loadFromBitmap(m_Pixels, m_PixelsWidth, m_PixelsHeight, m_PixelsFormat);
		else
			loadFromFile();
		
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}

	void Texture::destroy() {
		GLCall(glDeleteTextures(1, &m_TexID));
		m_TexID = 0;
		m_Width = 0;
		m_Height = 0;
		m_Format = TextureFormat::RED;
	}
}
