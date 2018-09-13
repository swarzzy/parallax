#pragma once
#ifndef _PARALLAX_GRAPHICS_FONT_H_
#define _PARALLAX_GRAPHICS_FONT_H_

#include <map>
#include "../../../hypermath/hypermath.h";

namespace prx {
	
	struct Character {
		unsigned int TexID;
		// TODO: ivec
		hpm::vec2	 Size;
		hpm::vec2	 Bearing;
		long		 Advance;

		Character(unsigned int tid, hpm::vec2 size, hpm::vec2 bearing, long advance)
			: TexID(tid), Size(size), Bearing(bearing), Advance(advance) {};
		Character() {};
	};

	class Font {
	private: 
		std::string		m_FilePath;
		unsigned int	m_Size;
		std::map<char, Character> m_Characters;
	
	public:
		Font(std::string_view filepath, int size);
		~Font();

		inline const std::string&				getFilePath()	const { return m_FilePath;	 };
		inline unsigned int						getSize()		const { return m_Size;		 };
		inline const std::map<char, Character>& getCharacters() const { return m_Characters; };

	private:
		void loadFont();
	};
}
#endif
