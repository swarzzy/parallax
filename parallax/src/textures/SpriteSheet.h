#pragma once
#ifndef _PARALLAX_TEXTURES_SPRITE_SHEET_H_
#define _PARALLAX_TEXTURES_SPRITE_SHEET_H_

#include <string>

#include "TextureBase.h"
#include "../Application/Application.h"
#include <unordered_map>

namespace prx {
	
	struct UV {
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
		float						duration; // in seconds

		Animation(std::string_view _name, unsigned int _framesNumber, std::vector<unsigned int> _UVIndices, float _duration = 1.0)
			: name(_name), 
			  framesNumber(_framesNumber), 
			  UVIndices(_UVIndices),
			  currentState(0), 
			  timeElapsed(0),
			  duration(_duration)
		{
			timePerState = static_cast<unsigned>(1000 * duration) / framesNumber;
		};

		inline void setDuration(float duration) noexcept {
			this->duration = duration;
			timePerState = static_cast<unsigned>(1000 * duration) / framesNumber;
		}
	};

	class SpriteSheet final : public TextureBase {
		PRX_DISALLOW_COPY_AND_MOVE(SpriteSheet)
	private:
		unsigned int	m_Columns;
		unsigned int	m_Rows;
		unsigned int	m_Tiles;
		UV*				m_UV;
		UV*				m_ReflectedUV;
		bool			m_Reflected;
		// Pointer to current selected UVs buffer to not check m_Reflected on every getTexCoords call
		UV*				m_CurrentUVBuffer;
		std::string		m_XMLPath;
		std::vector<Animation> m_Animations;
		// TODO: make picking animations by name faster
		std::unordered_map<std::string, unsigned int> m_AnimationList;

	public:
		SpriteSheet(std::string_view path);
		SpriteSheet(std::string_view path, unsigned int columns, unsigned int rows, bool reflected = false);
		~SpriteSheet();

		int addAnimation(std::string_view name, const std::vector<unsigned int>& mask, float duration = 1.0f);
		void setDuration(std::string_view animationName, float duration);

		const UV* getTexCoords(unsigned int animationID) const;
		const UV* getTexCoords(const std::string& animationName) const;
		inline unsigned int getAnimaionFrameCount(unsigned int animationID) const;
		inline unsigned int getAnimaionFrameCount(const std::string& animationName) const;
		inline unsigned int getAnimationCurrentFrame(unsigned int animationID) const;
		inline unsigned int getAnimationCurrentFrame(const std::string& animationName) const;
		inline const UV*	getFrameUVs(unsigned int frame) const;
		inline unsigned		getAnimationID(const std::string& animationName) const;

		void resetAnimations();

		void reflect(bool reflect);

	private:
		void initInternal() override;
		void destroyInternal() override;

		void parseXML();
	};
	
	inline unsigned int SpriteSheet::getAnimaionFrameCount(unsigned int animationID) const {
		return m_Animations[animationID].framesNumber;
	}

	inline unsigned SpriteSheet::getAnimaionFrameCount(const std::string& animationName) const {
		return m_Animations[m_AnimationList.find(animationName)->second].framesNumber;
	}


	inline unsigned int SpriteSheet::getAnimationCurrentFrame(unsigned int animationID) const {
		return m_Animations[animationID].currentState;
	}

	inline unsigned SpriteSheet::getAnimationCurrentFrame(const std::string& animationName) const {
		return m_Animations[m_AnimationList.find(animationName)->second].currentState;
	}


	inline const UV* SpriteSheet::getFrameUVs(unsigned int frame) const {
		if (frame > m_Tiles) {
			PRX_ERROR("SPRITE SHEET: Failed to get frame UVs. Wrong frame index/n-> SHEET: ", getFilePath());
			return nullptr;
		}
		if (frame < m_Tiles)
			return &m_UV[frame];
		else {
			PRX_ERROR("SPRITE SHEET: Incorrect UV index");
			return &m_UV[0];
		}
	}

	inline unsigned SpriteSheet::getAnimationID(const std::string& animationName) const {
		return m_AnimationList.find(animationName)->second;
	}
}
#endif