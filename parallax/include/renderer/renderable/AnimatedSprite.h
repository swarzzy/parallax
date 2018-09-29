#pragma once
#ifndef _PARALLAX_RENDERER_RENDERABLES_ANIMATED_SPRITE_H_
#define _PARALLAX_RENDERER_RENDERABLES_ANIMATED_SPRITE_H_
#include "Sprite.h"
#include "../../textures/SpriteSheet.h"

namespace prx {
	
	class AnimatedSprite : public Sprite {
	private:
		unsigned int m_AnimationID;
	public:
		AnimatedSprite(hpm::vec3 position, hpm::vec2 size, SpriteSheet* texture, unsigned int animationID)
			: Sprite(position, size, texture), m_AnimationID(animationID) {};

		inline const float* getUVs() const override;

		void playAnimation(unsigned int ID) {
			m_AnimationID = ID;
		}

	};
	
	inline const float* AnimatedSprite::getUVs() const {
		TexCoords tc = static_cast<SpriteSheet*>(m_Texture)->getTexCoords(m_AnimationID);

		m_UVs[0] = tc.lbX;
		m_UVs[1] = tc.lbY;
		m_UVs[2] = tc.ltX;
		m_UVs[3] = tc.ltY;
		m_UVs[4] = tc.rtX;
		m_UVs[5] = tc.rtY;
		m_UVs[6] = tc.rbX;
		m_UVs[7] = tc.rbY;
		return m_UVs;
	};
}
#endif
