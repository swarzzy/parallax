#include <textures/TextureBase.h>
#include <resources/ImageLoader.h>
#include <utils/error/ImageLoadingException.h>
#include "textures/Texture.h"

namespace prx {

	const unsigned int TextureBase::UV_ARRAY_SIZE = 8;

	const float TextureBase::DEFAULT_UV[8] = {
			0.0f, 0.0f,	0.0f, 1.0f,	1.0f, 1.0f,	1.0f, 0.0f
	};

	const float TextureBase::DEFAULT_REFLECT_UV[8] = {
			1.0f, 0.0f, 1.0f, 1.0f,	0.0f, 1.0f,	0.0f, 0.0f
	};

	const TextureWrap   TextureBase::DEFAULT_TEXTURE_WRAP = TextureWrap::REPEAT;
	const TextureFilter TextureBase::DEFAULT_TEXTURE_FILTER = TextureFilter::LINEAR;

	const byte TextureBase::EMPTY_TEXTURE_COLOR = 255;

	TextureBase::TextureBase(std::string_view filepath)
		: Resource(filepath),
		  m_TexID(0),
		  m_Width(0),
		  m_Height(0),
		  m_Format(TextureFormat::RGB),
		  m_WrapMode(defaultTextureWrap()),
		  m_FilterMode(defaultTextureFilter())
	{};

	TextureBase::TextureBase()
		: Resource(""),
		  m_TexID(0),
		  m_Width(0),
		  m_Height(0),
		  m_Format(TextureFormat::RGB),
		  m_WrapMode(defaultTextureWrap()),
		  m_FilterMode(defaultTextureFilter())
	{};

	void TextureBase::loadFromFile() {
		std::shared_ptr<Image> image;
		try {
			image = load_image(m_FilePath);
		}
		catch (ImageLoadingException& e) {
			PRX_ERROR("TEXTURE: ", e.what());
			loadEmpty(8, 8, TextureFormat::RED);
			return;
		}

		m_Width = image->getWigth();
		m_Height = image->getHeight();

		unsigned internalFormat;
		if (image->getFormat() == GL_RGB) {
			internalFormat = GL_RGB8;
			m_Format = TextureFormat::RGB;
		}
		else if (image->getFormat() == GL_RGBA) {
			internalFormat = GL_RGBA8;
			m_Format = TextureFormat::RGBA;
		}
		else {
			PRX_FATAL("TEXTURE: Could not create texture. Incorrect data format");
		}

		//GLCall(glTexStorage2D(GL_TEXTURE_2D, 1, internalFormat, m_Width, m_Height));
		//GLCall(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, image->getFormat(), GL_UNSIGNED_BYTE, image->getPixels()));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, image->getFormat(), GL_UNSIGNED_BYTE, image->getPixels()));
	}

	void TextureBase::setParameters(TextureWrap wrapMode, TextureFilter filterMode) {
		m_WrapMode = wrapMode;
		m_FilterMode = filterMode;
		updateParameters();
	}

	void TextureBase::loadFromBitmap(byte* pixels, unsigned width, unsigned height, TextureFormat format) {
		m_Width = width;
		m_Height = height;
		m_Format = format;

		unsigned internalFormat;
		unsigned pixelsFormat;

		if (m_Format == TextureFormat::RGB) {
			internalFormat = GL_RGB8;
			pixelsFormat = GL_RGB;
		}
		else if (m_Format == TextureFormat::RGBA) {
			internalFormat = GL_RGBA8;
			pixelsFormat = GL_RGBA;
		}
		else if (m_Format == TextureFormat::RED) {
			internalFormat = GL_RED;
			pixelsFormat = GL_RED;
		}
		else {
			PRX_FATAL("TEXTURE: Could not create texture from memory. Incorrect data format");
		}

		//GLCall(glTexStorage2D(GL_TEXTURE_2D, 1, internalFormat, m_Width, m_Height));
		//GLCall(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, image->getFormat(), GL_UNSIGNED_BYTE, image->getPixels()));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, pixelsFormat, GL_UNSIGNED_BYTE, pixels));
	}

	void TextureBase::loadEmpty(unsigned width, unsigned height, TextureFormat format) {
		m_Width = width;
		m_Height = height;
		m_Format = format;
		
		unsigned internalFormat;
		unsigned pixelsFormat;

		byte* data = nullptr;

		if (m_Format == TextureFormat::RGB) {
			internalFormat = GL_RGB8;
			pixelsFormat = GL_RGB;
			data = new byte[m_Width * m_Height * 3];
			memset(data, EMPTY_TEXTURE_COLOR, m_Width * m_Height * 3 * sizeof(byte));
		}
		else if (m_Format == TextureFormat::RGBA) {
			internalFormat = GL_RGBA8;
			pixelsFormat = GL_RGBA;
			data = new byte[m_Width * m_Height * 4];
			memset(data, EMPTY_TEXTURE_COLOR, m_Width * m_Height * 4 * sizeof(byte));
		}
		else if (m_Format == TextureFormat::RED) {
			internalFormat = GL_RED;
			pixelsFormat = GL_RED;
			data = new byte[m_Width * m_Height * 1];
			memset(data, EMPTY_TEXTURE_COLOR, m_Width * m_Height * 1 * sizeof(byte));
		}
		else {
			PRX_FATAL("TEXTURE: Could not create texture from memory. Incorrect data format");
		}

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, pixelsFormat, GL_UNSIGNED_BYTE, data));
	}

	void TextureBase::unload() {
		GLCall(glDeleteTextures(1, &m_TexID));
	}

	void TextureBase::updateParameters() {
		GLCall(glBindTexture(GL_TEXTURE_2D, m_TexID));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<int>(m_WrapMode)));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<int>(m_WrapMode)));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<int>(m_FilterMode)));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<int>(m_FilterMode)));

		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}

	unsigned TextureBase::getGLFormat(TextureFormat format) {
		switch (format) {
		case TextureFormat::RED:  return GL_RED;
		case TextureFormat::RGB:  return GL_RGB;
		case TextureFormat::RGBA: return GL_RGBA;
		default: return 0;
		}
	}

	unsigned TextureBase::getFormatDepth(TextureFormat format) {
		switch (format) {
		case TextureFormat::RED:  return 1;
		case TextureFormat::RGB:  return 3;
		case TextureFormat::RGBA: return 4;
		default: return 0;
		}
	}
}
