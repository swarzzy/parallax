#include <textures/TextureAtlas.h>

#include <utils/log/Log.h>
#include <utils/error_handling/GLErrorHandler.h>
#include <resources/ImageLoader.h>
#include <textures/Texture.h>

namespace prx {
	TextureAtlas::TextureAtlas(unsigned int width, unsigned int height, TextureFormat format) {
		m_Format = format;
		m_Width  = width;
		m_Height = height;

		unsigned int depth;
		if (format == TextureFormat::RED)
			depth = 1;
		if (format == TextureFormat::RGB)
			depth = 3;
		if (format == TextureFormat::RGBA)
			depth = 4;

		m_TextureAtlas = ftgl::texture_atlas_new(width, height, depth);
	}

	TextureAtlas::~TextureAtlas() {
		ftgl::texture_atlas_delete(m_TextureAtlas);
		GLCall(glDeleteTextures(1, &m_TexID));
	}

	void TextureAtlas::bind() const {
		GLCall(glBindTexture(GL_TEXTURE_2D, m_TexID));
	}

	void TextureAtlas::unbind() const {
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}

	hpm::vec4 TextureAtlas::add(unsigned char* pixels, unsigned width, unsigned height, TextureFormat format) {
		if (format != m_Format) {
			Log::message("TEXTURE ATLAS: Could not add region to the atlas. Incorrect data format", LOG_ERROR);
			ASSERT(false);
		}
		ftgl::ivec4 atl = ftgl::texture_atlas_get_region(m_TextureAtlas, width, height);
		if (atl.x < 0) {
			// TODO: Quiet logging
			//Log::message("TEXTURE ATLAS: Atlas is full. Can not add new region.", LOG_WARNING);
			return hpm::vec4(-1.0);
		}
		ftgl::texture_atlas_set_region(m_TextureAtlas, atl.x, atl.y, atl.width, atl.height, pixels, width);

		return hpm::vec4(atl.x, atl.y, atl.width, atl.height);
	}

	hpm::vec4 TextureAtlas::add(std::string_view path) {
		Image* image = ImageLoader::loadImage(path);

		if (image->getFormat() != getGLFormat(m_Format)) {
			Log::message("TEXTURE ATLAS: Could not add region to the atlas. Incorrect data format", LOG_ERROR);
			ASSERT(false);
		}
		ftgl::ivec4 atl = ftgl::texture_atlas_get_region(m_TextureAtlas, image->getWigth(), image->getHeight());
		if (atl.x < 0) {
			//Log::message("TEXTURE ATLAS: Atlas is full. Can not add new region.", LOG_WARNING);
			return hpm::vec4(-1.0);
		}
		ftgl::texture_atlas_set_region(m_TextureAtlas, atl.x, atl.y, atl.width, atl.height, image->getPixels(), image->getWigth());
		return hpm::vec4(atl.x, atl.y, atl.width, atl.height);
	}

	void TextureAtlas::resize(unsigned width, unsigned height) {
		if (width < m_TextureAtlas->width || height < m_TextureAtlas->height) {
			Log::message("TEXTURE ATLAS: Can not resize atlas. New size os less than old.", LOG_ERROR);
			return;
		}

		unsigned int depth;
		if (m_Format == TextureFormat::RED)
			depth = 1;
		if (m_Format == TextureFormat::RGB)
			depth = 3;
		if (m_Format == TextureFormat::RGBA)
			depth = 4;
		ftgl::texture_atlas_t* textureAtlasNew;
		textureAtlasNew = ftgl::texture_atlas_new(width, height, depth);

		ftgl::ivec4 atl = ftgl::texture_atlas_get_region(textureAtlasNew, m_TextureAtlas->width, m_TextureAtlas->height);
		if (atl.x < 0) {
			Log::message("TEXTURE ATLAS: Can not resize atlas", LOG_ERROR);
			return;
		}
		ftgl::texture_atlas_set_region(textureAtlasNew, atl.x, atl.y, atl.width, atl.height, m_TextureAtlas->data, m_TextureAtlas->width);
		ftgl::texture_atlas_delete(m_TextureAtlas);
		m_TextureAtlas = textureAtlasNew;

		m_Width = m_TextureAtlas->width;
		m_Height = m_TextureAtlas->height;
	}

	void TextureAtlas::update() {
		GLCall(glDeleteTextures(1, &m_TexID));
		unsigned int result;
		GLCall(glGenTextures(1, &result));

		GLCall(glBindTexture(GL_TEXTURE_2D, result));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		/*GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));*/

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
			Log::message("TEXTURE: Could not create texture. Incorrect data format", LOG_ERROR);
			ASSERT(false);
		}

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, m_TextureAtlas->data));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		m_TexID = result;
	}
}
