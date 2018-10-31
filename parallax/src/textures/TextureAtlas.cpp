#include <textures/TextureAtlas.h>

#include <utils/log/Log.h>
#include <utils/error_handling/GLErrorHandler.h>
#include <resources/ImageLoader.h>
#include <textures/Texture.h>
#include "utils/error/ImageLoadingException.h"

namespace prx {
	TextureAtlas::TextureAtlas(unsigned int width, unsigned int height, TextureFormat format)
		: TextureBase(""){
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

	hpm::vec4 TextureAtlas::add(unsigned char* pixels, unsigned width, unsigned height, TextureFormat format) {
		if (format != m_Format) {
			PRX_FATAL("TEXTURE ATLAS: Could not add region to the atlas. Incorrect data format");
		}
		ftgl::ivec4 atl = ftgl::texture_atlas_get_region(m_TextureAtlas, width, height);
		if (atl.x < 0) {
			PRX_WARN("TEXTURE ATLAS: Atlas is full. Can not add new region.");
			return hpm::vec4(-1.0);
		}
		ftgl::texture_atlas_set_region(m_TextureAtlas, atl.x, atl.y, atl.width, atl.height, pixels, width);

		return hpm::vec4(static_cast<float>(atl.x), static_cast<float>(atl.y), 
						 static_cast<float>(atl.width), static_cast<float>(atl.height));
	}

	hpm::vec4 TextureAtlas::add(std::string_view path) {
		std::shared_ptr<Image> image;
		try {
			 image = load_image(path);
		} catch (ImageLoadingException& e) {
			PRX_FATAL("TEXTURE ATLAS: ", e);
		}
		if (image->getFormat() != getGLFormat(m_Format)) {
			PRX_FATAL(LOG_LEVEL::LOG_ERROR, "TEXTURE ATLAS: Could not add region to the atlas. Incorrect data format");
		}
		ftgl::ivec4 atl = ftgl::texture_atlas_get_region(m_TextureAtlas, image->getWigth(), image->getHeight());
		if (atl.x < 0) {
			PRX_WARN("TEXTURE ATLAS: Atlas is full. Can not add new region.");
			return hpm::vec4(-1.0);
		}
		ftgl::texture_atlas_set_region(m_TextureAtlas, atl.x, atl.y, atl.width, atl.height, image->getPixels(), image->getWigth());
		
		return hpm::vec4(static_cast<float>(atl.x), static_cast<float>(atl.y),
					     static_cast<float>(atl.width), static_cast<float>(atl.height));
	}

	void TextureAtlas::resize(unsigned width, unsigned height) {
		if (width < m_TextureAtlas->width || height < m_TextureAtlas->height) {
			PRX_WARN("TEXTURE ATLAS: Can not resize atlas. New size os less than old.");
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
			PRX_ERROR("TEXTURE ATLAS: Can not resize atlas");
			return;
		}
		ftgl::texture_atlas_set_region(textureAtlasNew, atl.x, atl.y, atl.width, atl.height, m_TextureAtlas->data, m_TextureAtlas->width);
		ftgl::texture_atlas_delete(m_TextureAtlas);
		m_TextureAtlas = textureAtlasNew;

		m_Width =  static_cast<unsigned>(m_TextureAtlas->width);
		m_Height = static_cast<unsigned>(m_TextureAtlas->height);
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
			PRX_FATAL("TEXTURE: Could not create texture. Incorrect data format");
		}

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, m_TextureAtlas->data));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		m_TexID = result;
	}
}
