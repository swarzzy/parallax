#include <Fonts/Font.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <utils/log/Log.h>

#include <utils/error_handling/FTErrorHandler.h>
#include <utils/error_handling/GLErrorHandler.h>

#include <ext/ftgl/texture-atlas.h>
#include <textures/Texture.h>

namespace prx {
	Font::Font(std::string_view filepath, std::string_view name, int size, float scale) 
		: m_FilePath(filepath),
		  m_Name(name),
		  m_Size(size), 
		  m_Scale(scale), 
		  m_FontAtlas(nullptr)
	{
		loadFontFromFile();
	}

	Font::Font(std::string_view name, const unsigned char* data, size_t dataSize, int size, float scale) 
		: m_FilePath(""),
		  m_Name(name),
		  m_Size(size), 
		  m_Scale(scale), 
		  m_FontAtlas(nullptr) 
	{
		loadFontFromBinary(data, dataSize);
	}

	Font::~Font() {
		delete m_FontAtlas;
	}

	void Font::loadFontFromBinary(const unsigned char* data, size_t size) {
		USE_PARALLAX_FREETYPE_DEBUGGER

		FT_Library ft;
		FT_Face face;

		FTCall(FT_Init_FreeType(&ft));
		FTCall(FT_New_Memory_Face(ft, data, size, 0, &face));

		FTCall(FT_Set_Pixel_Sizes(face, 0, m_Size));

		//GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));

		m_FontAtlas = new TextureAtlas(512, 512, TextureFormat::RED);

		// FreeType transformation matrix to flip glyph y-coords 
		FT_Matrix matrix = {
		static_cast<int>(((1.0) * 0x10000L)),
		static_cast<int>(((0.0) * 0x10000L)),
		static_cast<int>(((0.0) * 0x10000L)),
		static_cast<int>(((-1.0) * 0x10000L)) };

		FT_Set_Transform(face, &matrix, NULL);

		for (int i = 0; i < 128; i++) {

			char ch = static_cast<char>(i);

			FTCall(FT_Load_Char(face, ch, FT_LOAD_RENDER));
			hpm::vec4 coords = m_FontAtlas->add(face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows, TextureFormat::RED);
			if (coords.x < 0.0f) {
				m_FontAtlas->resize(m_FontAtlas->getWidth() * 1.5, m_FontAtlas->getHeight() * 1.5);

				// Shifting all old chars coords by 1 because of 
				// texture atlas resize method implementation

				for (auto& ch : m_Characters) {
					ch.second.AtlasCoords.x += 1;
					ch.second.AtlasCoords.y += 1;
				}

				coords = m_FontAtlas->add(face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows, TextureFormat::RED);
			}

			m_Characters.emplace(std::piecewise_construct, std::forward_as_tuple(ch), std::forward_as_tuple(
				coords,
				hpm::vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				hpm::vec2(face->glyph->bitmap_left, face->glyph->bitmap.rows - face->glyph->bitmap_top),
				face->glyph->advance.x
			));
		}
		m_FontAtlas->update();

		m_FontAtlas->bind();

		// Passing red chanel value into other channels. So we get texture with white 
		// non-transparent glyph and 100% transparent background. In shaders we can 
		// just multiply each pixel of texture by a color to get glyph color we need.

		int swizzleMask[] = { GL_RED, GL_RED, GL_RED, GL_RED };
		GLCall(glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask));
		m_FontAtlas->unbind();

		FTCall(FT_Done_Face(face));
		FTCall(FT_Done_FreeType(ft));
	}

	void Font::loadFontFromFile() {
		
		USE_PARALLAX_FREETYPE_DEBUGGER

		FT_Library ft;
		FT_Face face;
		
		FTCall(FT_Init_FreeType(&ft));
		FTCall(FT_New_Face(ft, m_FilePath.c_str(), 0, &face));

		FTCall(FT_Set_Pixel_Sizes(face, 0, m_Size));

		GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));

		m_FontAtlas = new TextureAtlas(512, 512, TextureFormat::RED);

		// FreeType transformation matrix to flip glyph y-coords 
		FT_Matrix matrix = {
		static_cast<int>(((1.0) * 0x10000L)),
		static_cast<int>(((0.0) * 0x10000L)),
		static_cast<int>(((0.0) * 0x10000L)),
		static_cast<int>(((-1.0) * 0x10000L)) };

		FT_Set_Transform(face, &matrix, NULL);

		for (int i = 0; i < 128; i++) {

			char ch = static_cast<char>(i);

			FTCall(FT_Load_Char(face, ch, FT_LOAD_RENDER));
			hpm::vec4 coords =  m_FontAtlas->add(face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows, TextureFormat::RED);
			if (coords.x < 0.0f) {
				m_FontAtlas->resize(m_FontAtlas->getWidth() * 1.5, m_FontAtlas->getHeight() * 1.5);
				
				// Shifting all old chars coords by 1 because of 
				// texture atlas resize method implementation
				
				for (auto& ch : m_Characters) {
					ch.second.AtlasCoords.x += 1;
					ch.second.AtlasCoords.y += 1;
				}

				coords = m_FontAtlas->add(face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows, TextureFormat::RED);
			}

			m_Characters.emplace(std::piecewise_construct, std::forward_as_tuple(ch), std::forward_as_tuple(
									coords,
									hpm::vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
									hpm::vec2(face->glyph->bitmap_left, face->glyph->bitmap.rows - face->glyph->bitmap_top),
									face->glyph->advance.x
								));
		}
		m_FontAtlas->update();

		m_FontAtlas->bind();

		// Passing red chanel value into other channels. So we get texture with white 
		// non-transparent glyph and 100% transparent background. In shaders we can 
		// just multiply each pixel of texture by a color to get glyph color we need.

		int swizzleMask[] = { GL_RED, GL_RED, GL_RED, GL_RED };
		GLCall(glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask));
		m_FontAtlas->unbind();

		FTCall(FT_Done_Face(face));
		FTCall(FT_Done_FreeType(ft));
	}
}
