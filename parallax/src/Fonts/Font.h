#pragma once
#ifndef _PARALLAX_GRAPHICS_FONT_H_
#define _PARALLAX_GRAPHICS_FONT_H_

#include <map>
#include <hypermath.h>
#include "../ext/ftgl/texture-atlas.h"
#include "../textures/TextureAtlas.h"

namespace prx {
	
	struct Character {
		hpm::vec4 AtlasCoords;
		hpm::vec2 Size;
		hpm::vec2 Bearing;
		long	  Advance;

		Character(hpm::vec4 coords, hpm::vec2 size, hpm::vec2 bearing, long advance)
			: AtlasCoords(coords), Size(size), Bearing(bearing), Advance(advance) {};
		Character() {}; // TODO: Get rid of this constructor (only renderer uses it for no reason)
	};

	class Font {
		//PRX_DISALLOW_COPY_AND_MOVE(Font)
	private: 
		std::string					m_FilePath;
		std::string					m_Name;
		unsigned int				m_Size;
		float						m_Scale;
		std::map<char, Character>	m_Characters;
		TextureAtlas*				m_FontAtlas;
		bool						m_LoadedFromFile;

		const unsigned char*		m_BinaryData;
		size_t						m_BinaryDataSize;

	public:
		Font(std::string_view filepath, std::string_view name, int size, float scale = 1.0f);
		Font(std::string_view name, const unsigned char* data, long dataSize, int size, float scale = 1.0f);
		~Font();

		void reloadWithNewScale(float scale);

		inline const std::string&				getFilePath()	const { return m_FilePath;	 };
		inline const std::string&				getName()		const { return m_Name;		 };
		inline unsigned int						getSize()		const { return m_Size;		 };
		inline float							getScale()		const { return m_Scale;		 };
		inline const std::map<char, Character>& getCharacters() const { return m_Characters; };
		inline const TextureAtlas&				getFontAtlas()  const { return *m_FontAtlas; };

	private:
		void loadFontFromFile();
		void loadFontFromBinary(const unsigned char* data, long size);
	};
}
#endif
