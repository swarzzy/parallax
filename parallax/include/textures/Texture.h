#pragma once
#ifndef _PARALLAX_TEXTURES_TEXTURE_H_
#define _PARALLAX_TEXTURES_TEXTURE_H_

#include <string_view>

#include "TextureBase.h"

namespace prx {

	class Texture : public TextureBase {
	private:
		std::string  m_Path;
	
	public:
		Texture() {};
		Texture(std::string_view path);
		Texture(unsigned char* data, unsigned int width, unsigned int height, TextureFormat format);
		~Texture();

	private:
		unsigned int load();
		unsigned int loadFromBitmap(unsigned char* data);
	};

}
#endif