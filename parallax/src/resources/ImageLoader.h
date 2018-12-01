#pragma once
#ifndef _PARALLAX_UTILS_IMAGELOADER_H_
#define _PARALLAX_UTILS_IMAGELOADER_H_

#include <GL/gl3w.h>
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

		inline const unsigned int	getWigth()	const noexcept { return m_Width;  }
		inline const unsigned int	getHeight() const noexcept { return m_Height; }
		inline const GLenum			getFormat() const noexcept { return m_Format; }
		inline const unsigned char* getPixels() const noexcept { return m_Pixels; }
	};

	std::shared_ptr<Image> load_image(std::string_view path);
}
#endif