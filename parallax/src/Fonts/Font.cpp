#include "Font.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include "../utils/log/Log.h"

#include "../utils/error_handling/FTErrorHandler.h"
#include "../utils/GLErrorHandler.h"

namespace prx {
	Font::Font(std::string_view filepath, int size) 
		: m_FilePath(filepath), m_Size(size){
		loadFont();
	}

	Font::~Font() {
		for (auto& character : m_Characters) {
			GLCall(glDeleteTextures(1, &character.second.TexID));
		}
	}

	void Font::loadFont() {
		
		USE_PARALLAX_FREETYPE_DEBUGGER

		FT_Library ft;
		FT_Face face;
		
		FTCall(FT_Init_FreeType(&ft));
		FTCall(FT_New_Face(ft, m_FilePath.c_str(), 0, &face));

		FTCall(FT_Set_Pixel_Sizes(face, 0, m_Size));

		GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));

		for (int i = 0; i < 128; i++) {
			
			char ch = static_cast<char>(i);
			
			FTCall(FT_Load_Char(face, ch, FT_LOAD_RENDER));

			unsigned int texture;
			GLCall(glGenTextures(1, &texture));
			GLCall(glBindTexture(GL_TEXTURE_2D, texture));
			GLCall(glTexImage2D(
								GL_TEXTURE_2D,
								0,
								GL_RED,
								face->glyph->bitmap.width,
								face->glyph->bitmap.rows,
								0,
								GL_RED,
								GL_UNSIGNED_BYTE,
								face->glyph->bitmap.buffer)
								);
			
			int swizzleMask[] = { GL_RED, GL_RED, GL_RED, GL_RED };
			GLCall(glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask));

			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

			m_Characters.emplace(std::piecewise_construct, std::forward_as_tuple(ch), std::forward_as_tuple(
									texture,
									hpm::vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
									hpm::vec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
									face->glyph->advance.x
			));
		}
		FTCall(FT_Done_Face(face));
		FTCall(FT_Done_FreeType(ft));
	}
}
