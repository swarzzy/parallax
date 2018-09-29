#pragma once
#ifndef _PARALLAX_TEXTURES_SPRITE_SHEET_H_
#define _PARALLAX_TEXTURES_SPRITE_SHEET_H_

#include <string>

#include "TextureBase.h"
#include "../Parallax.h"

namespace prx {
	
	struct TexCoords {
		// left bottom
		float lbX;
		float lbY;
		// left top
		float ltX;
		float ltY;
		// right top
		float rtX;
		float rtY;
		// right bottom
		float rbX;
		float rbY;
	};

	class SpriteSheet : public TextureBase {
	private:
		std::string		m_Path;
		unsigned int	m_Columns;
		unsigned int	m_Rows;
		unsigned int	m_Tiles;
		TexCoords*		m_TexCoords;
		unsigned int	m_TimePerState;
		
		mutable unsigned int		m_CurrentState;
		mutable unsigned long long	m_TimeElapsed;

	public:
		SpriteSheet() {};
		SpriteSheet(std::string_view path, unsigned int columns, unsigned int rows);
		~SpriteSheet();
		
		const TexCoords& getTexCoords() const;

	private:
		unsigned int load();
	};	
}
#endif
