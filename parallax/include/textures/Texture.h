#pragma once
#ifndef _PARALLAX_TEXTURES_TEXTURE_H_
#define _PARALLAX_TEXTURES_TEXTURE_H_

#include <string_view>
#include "../Common.h"
#include "TextureBase.h"

namespace prx {

	class Texture : public TextureBase {
	public:
		PRX_DISALLOW_COPY_AND_MOVE(Texture)

		Texture() {}
		Texture(std::string_view name, std::string_view path);
		Texture(unsigned char* data, unsigned int width, unsigned int height, TextureFormat format);
		~Texture();

	private:
		unsigned int load();
		unsigned int loadFromBitmap(unsigned char* data);
	};

}
#endif