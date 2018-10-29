#include <resources/ImageLoader.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../../ext/stb/stb_image.h"
#include "../utils/error/ImageLoadingException.h"

namespace prx {

	Image::Image(unsigned width, unsigned height, GLenum format, unsigned char* pixels)
		: m_Width(width), m_Height(height), m_Format(format), m_Pixels(pixels) {}

	Image::~Image() {
		stbi_image_free(m_Pixels);
	}

	std::shared_ptr<Image> load_image(std::string_view path) {
		stbi_set_flip_vertically_on_load(true);

		int width, height, componentsCount;

		unsigned char* data = stbi_load(path.data(), &width, &height, &componentsCount, 0);
		if (data == nullptr) {
			throw ImageLoadingException(path.data());
		}

			GLenum format;
			if (componentsCount == 1)
				format = GL_RED;
			else if (componentsCount == 3)
				format = GL_RGB;
			else if (componentsCount == 4)
				format = GL_RGBA;

			return std::make_shared<Image>(width, height, format, data);
	}
}
