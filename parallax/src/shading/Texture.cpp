#include "Texture.h"
#include "../resources/ImageLoader.h"
#include "../utils/error_handling/GLErrorHandler.h"


namespace prx {
	Texture::Texture(std::string_view path) 
	: m_Path(path){
		m_TexID = load();
	}

	Texture::~Texture() {
		
	}

	void Texture::bind() const {
		GLCall(glBindTexture(GL_TEXTURE_2D, m_TexID));
	}

	void Texture::unbind() const {
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
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
		if (image->getFormat() == GL_RGB)
			internalFormat = GL_RGB8;
		else if (image->getFormat() == GL_RGBA)
			internalFormat = GL_RGBA8;
		else {
			internalFormat = GL_RGB;
			std::string msg("Image: ");
			msg + m_Path + " has incompatible format.";
			Log::message(msg, LOG_WARNING);
		}
			
		//GLCall(glTexStorage2D(GL_TEXTURE_2D, 1, internalFormat, m_Width, m_Height));
		//GLCall(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, image->getFormat(), GL_UNSIGNED_BYTE, image->getPixels()));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, image->getFormat(), GL_UNSIGNED_BYTE, image->getPixels()));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));

		delete image;

		return result;
	}

}
