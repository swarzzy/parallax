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

	struct Animation {
		std::string	 name;
		unsigned int framesNumber;
		unsigned int timePerState;
		std::vector<unsigned int> UVIndices;
		
		mutable unsigned int		currentState;
		mutable unsigned long long	timeElapsed;

		Animation() {};
		Animation(std::string_view _name, unsigned int _framesNumber, std::vector<unsigned int> _UVIndices)
			: name(_name), framesNumber(_framesNumber), UVIndices(_UVIndices),
			currentState(0), timeElapsed(0) {
			timePerState = 1000 / framesNumber;
		};
	};

	class SpriteSheet : public TextureBase {
	private:
		std::string		m_Path;
		unsigned int	m_Columns;
		unsigned int	m_Rows;
		unsigned int	m_Tiles;
		TexCoords*		m_TexCoords;
		std::vector<Animation> m_Animations;
		

	public:
		SpriteSheet() {};
		SpriteSheet(std::string_view path, unsigned int columns, unsigned int rows);
		~SpriteSheet();

		unsigned int addAnimation(std::string_view name, const std::vector<unsigned int>& mask);

		const TexCoords& getTexCoords(unsigned int animationID) const;

	private:
		unsigned int load();
	};	
}
#endif
