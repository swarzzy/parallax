#pragma once

#ifndef _IMAGELOADER_H_
#define _IMAGELOADER_H_

#include <string_view>
#include <iterator>

#include "../utils/log/Log.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace prx {
	
	class Image {
	private:
		unsigned int	m_Width;
		unsigned int	m_Height;
		GLenum			m_Format;
		unsigned char*	m_Pixels;
	public:
		Image(unsigned int width, unsigned int height, GLenum format, unsigned char* pixels)
			: m_Width(width), m_Height(height), m_Format(format), m_Pixels(pixels) {
		}
		~Image() { stbi_image_free(m_Pixels); }
		inline const unsigned int	getWigth()	const { return m_Width;  }
		inline const unsigned int	getHeight() const { return m_Height; }
		inline const GLenum			getFormat() const { return m_Format; }
		inline const unsigned char* getPixels() const { return m_Pixels; }
	};

	class ImageLoader {
	public:
		static Image* loadImage(std::string_view path) {
			stbi_set_flip_vertically_on_load(true);
			
			int width, height, componentsCount;
			
			unsigned char *data = stbi_load(path.data(), &width, &height, &componentsCount, 0);
			
			if (data) {
				GLenum format;
				if (componentsCount == 1)
					format = GL_RED;
				else if (componentsCount == 3)
					format = GL_RGB;
				else if (componentsCount == 4)
					format = GL_RGBA;

				return new Image(width, height, format, data);
			} else {
				Log::message("Image loader error! Can`t load image", LOG_ERROR);
				return nullptr;
			}
		}
	};
}
#endif