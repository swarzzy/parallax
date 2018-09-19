#pragma once
#ifndef _PARALLAX_GRAPHICS_FONT_H_
#define _PARALLAX_GRAPHICS_FONT_H_

#include <map>
#include <hypermath.h>;
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
		Character() {};
	};

	class Font {
	private: 
		std::string					m_FilePath;
		unsigned int				m_Size;
		float						m_Scale;
		std::map<char, Character>	m_Characters;

	public:
		TextureAtlas*				m_FontAtlas;
		Font() {};
		Font(std::string_view filepath, int size, float scale = 1.0f);
		~Font();

		inline const std::string&				getFilePath()	const { return m_FilePath;	 };
		inline unsigned int						getSize()		const { return m_Size;		 };
		inline float							getScale()		const { return m_Scale;		 };
		inline const std::map<char, Character>& getCharacters() const { return m_Characters; };
		inline const TextureAtlas&				getFontAtlas()  const { return *m_FontAtlas; };

	private:
		void loadFont();
	};
}
#endif
