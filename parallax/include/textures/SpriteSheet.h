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
		TexCoords*		m_ReflectedTexCoords;
		bool			m_Reflected;
		// Pointer to current selected UVs buffer to not check m_Reflected on every getTexCoords call
		TexCoords*		m_CurrentUVBuffer;
		std::vector<Animation> m_Animations;
		// Caching current application pointer to not request it in every getTexCoords call.
		// It`s assumed that the lifetime of sprite is not longer that the lifetime of application
		const Application* m_CurrentApplication;
		

	public:
		SpriteSheet() {};
		SpriteSheet(std::string_view path, unsigned int columns, unsigned int rows, bool reflected = false);
		~SpriteSheet();

		unsigned int addAnimation(std::string_view name, const std::vector<unsigned int>& mask);

		const TexCoords& getTexCoords(unsigned int animationID) const;
		inline unsigned int getAnimaionFrameCount(unsigned int animationID) const;
		inline unsigned int getAnimationCurrentFrame(unsigned int animationID) const;
		inline const TexCoords&	getFrameUVs(unsigned int frame) const;

		void resetAnimations();

		void reflect(bool reflect);

	private:
		unsigned int load();
	};
	
	inline unsigned int SpriteSheet::getAnimaionFrameCount(unsigned int animationID) const {
		return m_Animations[animationID].framesNumber;
	}

	inline unsigned int SpriteSheet::getAnimationCurrentFrame(unsigned int animationID) const {
		return m_Animations[animationID].currentState;
	}

	inline const TexCoords&	SpriteSheet::getFrameUVs(unsigned int frame) const {
		if (frame < m_Tiles)
			return m_TexCoords[frame];
		else {
			Log::message(LOG_LEVEL::LOG_ERROR, "SPRITE SHEET: Incorrect UV index");
			return m_TexCoords[0];
		}
	}
}
#endif
