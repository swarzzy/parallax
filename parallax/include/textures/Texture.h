#pragma once
#ifndef _PARALLAX_TEXTURES_TEXTURE_H_
#define _PARALLAX_TEXTURES_TEXTURE_H_

#include "../Common.h"
#include "TextureBase.h"

namespace prx {

	class Texture : public TextureBase {
		PRX_DISALLOW_COPY_AND_MOVE(Texture)
	private:
		byte*			m_Pixels;
		unsigned		m_PixelsWidth;
		unsigned		m_PixelsHeight;
		TextureFormat	m_PixelsFormat;

	public:

		Texture() : TextureBase("") {};
		explicit Texture(std::string_view path);
		Texture(byte* data, unsigned int width, unsigned int height, TextureFormat format);
		~Texture();

		void initInternal() override;
		void destroyInternal() override;
	};
}
#endif