#include "Texture.h"
#include "../utils/error_handling/GLErrorHandler.h"
#include "../resources/ImageLoader.h"

namespace prx {

	Texture::Texture(std::string_view path)
		: TextureBase(path)
	{
		loadFromFile();
	}

	Texture::Texture(byte* data, unsigned int width, unsigned int height, TextureFormat format)
		: TextureBase("")
	{
		loadFromBitmap(data, width, height, format);
	}

	
	Texture::Texture(unsigned width, unsigned height, TextureFormat format) 
		: TextureBase("") 
	{
		loadEmpty(width, height, format);
	}
	

	Texture::~Texture() {
		GLCall(glDeleteTextures(1, &m_TexID));
	}
}
