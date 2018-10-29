#pragma once
#ifndef _PARALLAX_TEXTURES_TEXTURES_ATLAS_H_
#define _PARALLAX_TEXTURES_TEXTURES_ATLAS_H_

#include "../ext/ftgl/texture-atlas.h"

#include "TextureBase.h"
#include <hypermath.h>

namespace prx {
	
	class Texture;

	// Totally bad and unsafe. Works only with fonts.
	class TextureAtlas : public TextureBase {
	private:
		ftgl::texture_atlas_t* m_TextureAtlas;

	public:
		TextureAtlas(unsigned int width, unsigned int height, TextureFormat format);
		~TextureAtlas();

		// Add a new region to the atlas. Does not affects on actual rendering API texture.
		hpm::vec4 add(unsigned char* pixels, unsigned int width, unsigned int height, TextureFormat format);
		// Add a new region to the atlas. Does not affects on actual rendering API texture.
		hpm::vec4 add(std::string_view path);

		// Create new atlas and copy all data from old
		// Totally bad and unsafe. Not use it ever! Shifts all old tex coords by 1
		void resize(unsigned int width, unsigned int height);
		
		// Rebuilds actual rendering API texture with new added regions.
		void update();

		inline unsigned int getUsage()  const { return static_cast<unsigned int>(m_TextureAtlas->used);   };
		inline unsigned int getWidth()  const { return static_cast<unsigned int>(m_TextureAtlas->width);  };
		inline unsigned int getHeight() const { return static_cast<unsigned int>(m_TextureAtlas->height); };
	};

}
#endif