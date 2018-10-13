#pragma once
#ifndef _PARALLAX_RENDERER_RENDERABLES_ANIMATED_SPRITE_H_
#define _PARALLAX_RENDERER_RENDERABLES_ANIMATED_SPRITE_H_
#include "Sprite.h"
#include "../../textures/SpriteSheet.h"

namespace prx {
	
	enum class AnimationState { PLAY, LOOP, STOP };

	class AnimatedSprite : public Sprite {
	private:
		unsigned int m_AnimationID;
		// Store sprite sheet as dedicate sprite sheet pointer to not cast TextureBase 
		// to the sheet every getUVs call
		SpriteSheet*	m_SpriteSheet;
		mutable AnimationState	m_AnimationState;
		unsigned int m_DefaultFrame;
	public:
		// TODO: setting default frame
		AnimatedSprite(hpm::vec2 position, hpm::vec2 size, SpriteSheet* texture, unsigned int animationID)
			: Sprite(position, size, texture), m_AnimationID(animationID), 
			m_SpriteSheet(texture), m_AnimationState(AnimationState::STOP), m_DefaultFrame(0) {
			// It`s setting UVs two times, here and in renderable constructor
			setDefaultUVs();
		};

		AnimatedSprite(float x, float y, float width, float height, SpriteSheet* texture, unsigned int animationID)
			: Sprite(x, y, width, height, texture), m_AnimationID(animationID),
			m_SpriteSheet(texture), m_AnimationState(AnimationState::STOP), m_DefaultFrame(0) {
			setDefaultUVs();
		};

		AnimatedSprite(float width, float height, SpriteSheet* texture, unsigned int animationID)
			: Sprite(width, height, texture), m_AnimationID(animationID),
			m_SpriteSheet(texture), m_AnimationState(AnimationState::STOP), m_DefaultFrame(0) {
			setDefaultUVs();
		};

		inline const float* getUVs() const override;

		inline void reflect(bool reflect) override;

		inline void loopAnimation(unsigned int ID);
		inline void playAnimation(unsigned int ID);
		inline void stopAnimation();
		
		inline AnimationState getAnimationState();
	
	private:
		void setDefaultUVs() override;
		void setReflectDefaultUVs() override {};
	};
	
	
	inline const float* AnimatedSprite::getUVs() const {
		if (m_AnimationState != AnimationState::STOP) {
			if (m_AnimationState == AnimationState::LOOP) {
				const TexCoords& tc = m_SpriteSheet->getTexCoords(m_AnimationID);

				m_UVs[0] = tc.lbX;
				m_UVs[1] = tc.lbY;
				m_UVs[2] = tc.ltX;
				m_UVs[3] = tc.ltY;
				m_UVs[4] = tc.rtX;
				m_UVs[5] = tc.rtY;
				m_UVs[6] = tc.rbX;
				m_UVs[7] = tc.rbY;

			}
			else
				if (m_AnimationState == AnimationState::PLAY) {
					if (m_SpriteSheet->getAnimationCurrentFrame(m_AnimationID)
						< m_SpriteSheet->getAnimaionFrameCount(m_AnimationID) - 1) {

						const TexCoords& tc = m_SpriteSheet->getTexCoords(m_AnimationID);

						m_UVs[0] = tc.lbX;
						m_UVs[1] = tc.lbY;
						m_UVs[2] = tc.ltX;
						m_UVs[3] = tc.ltY;
						m_UVs[4] = tc.rtX;
						m_UVs[5] = tc.rtY;
						m_UVs[6] = tc.rbX;
						m_UVs[7] = tc.rbY;
					}
					else {
						m_AnimationState = AnimationState::STOP;
						m_SpriteSheet->resetAnimations();
					}
				}
		}
		return m_UVs;
	};

	inline void AnimatedSprite::reflect(bool reflect) {
		m_SpriteSheet->reflect(reflect);
	}

	inline void AnimatedSprite::loopAnimation(unsigned ID) {
		m_AnimationID = ID;
		m_AnimationState = AnimationState::LOOP;
	}

	inline void AnimatedSprite::playAnimation(unsigned ID) {
		m_AnimationID = ID;
		m_AnimationState = AnimationState::PLAY;
	}

	inline void AnimatedSprite::stopAnimation() {
		m_AnimationState = AnimationState::STOP;
	}

	inline AnimationState AnimatedSprite::getAnimationState() {
		return m_AnimationState;
	}

	inline void AnimatedSprite::setDefaultUVs() {
		const TexCoords& tc = m_SpriteSheet->getFrameUVs(m_DefaultFrame);
		
		m_UVs[0] = tc.lbX;
		m_UVs[1] = tc.lbY;
		m_UVs[2] = tc.ltX;
		m_UVs[3] = tc.ltY;
		m_UVs[4] = tc.rtX;
		m_UVs[5] = tc.rtY;
		m_UVs[6] = tc.rbX;
		m_UVs[7] = tc.rbY;
	}

}
#endif
