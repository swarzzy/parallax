#include <textures/Texture.h>
#include <utils/error_handling/GLErrorHandler.h>
#include <resources/ImageLoader.h>

namespace prx {
	Texture::Texture(std::string_view path) 
		: m_Path(path) {
		m_TexID = load();
	}

	Texture::Texture(unsigned char* data, unsigned int width, unsigned int height, TextureFormat format)
		: m_Path("") {
		m_Width = width;
		m_Height = height;
		m_Format = format;
		m_TexID = loadFromBitmap(data);
	}

	Texture::~Texture() {
		GLCall(glDeleteTextures(1, &m_TexID));
	}

	unsigned Texture::load() {
		Image* image = ImageLoader::loadImage(m_Path);

		m_Width = image->getWigth();
		m_Height = image->getHeight();

		unsigned int result;
		GLCall(glGenTextures(1, &result));

		GLCall(glBindTexture(GL_TEXTURE_2D, result));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

		GLenum internalFormat;
		if (image->getFormat() == GL_RGB) {
			internalFormat = GL_RGB8;
			m_Format = TextureFormat::RGB;
		}
		else if (image->getFormat() == GL_RGBA) {
			internalFormat = GL_RGBA8;
			m_Format = TextureFormat::RGBA;
		}
		else {
			Log::message(LOG_LEVEL::LOG_FATAL, "TEXTURE: Could not create texture. Incorrect data format");
			ASSERT(false);
		}
			
		//GLCall(glTexStorage2D(GL_TEXTURE_2D, 1, internalFormat, m_Width, m_Height));
		//GLCall(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, image->getFormat(), GL_UNSIGNED_BYTE, image->getPixels()));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, image->getFormat(), GL_UNSIGNED_BYTE, image->getPixels()));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));

		delete image;

		return result;
	}

	unsigned Texture::loadFromBitmap(unsigned char* data) {

		unsigned int result;
		GLCall(glGenTextures(1, &result));

		GLCall(glBindTexture(GL_TEXTURE_2D, result));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

		GLenum internalFormat;
		GLenum format;
		if (m_Format == TextureFormat::RGB) {
			internalFormat = GL_RGB8;
			format = GL_RGB;
		}
		else if (m_Format == TextureFormat::RGBA) {
			internalFormat = GL_RGBA8;
			format = GL_RGBA;
		}
		else if (m_Format == TextureFormat::RED) {
			internalFormat = GL_RED;
			format = GL_RED;
		}
		else {
			Log::message(LOG_LEVEL::LOG_FATAL, "TEXTURE: Could not create texture. Incorrect data format");
			ASSERT(false);
		}

		//GLCall(glTexStorage2D(GL_TEXTURE_2D, 1, internalFormat, m_Width, m_Height));
		//GLCall(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, image->getFormat(), GL_UNSIGNED_BYTE, image->getPixels()));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));

		return result;
	}

}
