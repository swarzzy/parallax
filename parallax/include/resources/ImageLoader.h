#pragma once

#ifndef _IMAGELOADER_H_
#define _IMAGELOADER_H_

#include <string_view>

#include "../../ext/GL/glew.h"
#include "../utils/log/Log.h"

namespace prx {
	
	class Image {
	private:
		unsigned int	m_Width;
		unsigned int	m_Height;
		GLenum			m_Format;
		unsigned char*	m_Pixels;
	public:
		Image(unsigned int width, unsigned int height, GLenum format, unsigned char* pixels);
		~Image();

		inline const unsigned int	getWigth()	const { return m_Width;  }
		inline const unsigned int	getHeight() const { return m_Height; }
		inline const GLenum			getFormat() const { return m_Format; }
		inline const unsigned char* getPixels() const { return m_Pixels; }
	};

	class ImageLoader {
	public:
		static Image* loadImage(std::string_view path);
	};
}
#endif