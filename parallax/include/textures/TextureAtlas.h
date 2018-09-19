#pragma once
#ifndef _PARALLAX_TEXTURES_ATLAS_H_
#define _PARALLAX_TEXTURES_ATLAS_H_

#include <string_view>

#include "../ext/ftgl/texture-atlas.h"

#include "TextureBase.h"
#include <hypermath.h>

namespace prx {
	
	class Texture;

	class TextureAtlas : public TextureBase {
	private:
		ftgl::texture_atlas_t* m_TextureAtlas;

	public:
		TextureAtlas(unsigned int width, unsigned int height, TextureFormat format);
		~TextureAtlas();

		void bind() const override;
		void unbind() const override;

		// Add a new region to the atlas. Does not affects on actual rendering API texture.
		hpm::vec4 add(unsigned char* pixels, unsigned int width, unsigned int height, TextureFormat format);
		// Add a new region to the atlas. Does not affects on actual rendering API texture.
		hpm::vec4 add(std::string_view path);
		
		// Rebuilds actual rendering API texture with new added regions.
		void update();

		inline unsigned int getUsage() const { return m_TextureAtlas->used; };
	};

}
#endif