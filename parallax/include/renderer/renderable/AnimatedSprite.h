#pragma once
#ifndef _PARALLAX_RENDERER_RENDERABLES_ANIMATED_SPRITE_H_
#define _PARALLAX_RENDERER_RENDERABLES_ANIMATED_SPRITE_H_
#include "Sprite.h"
#include "../../textures/SpriteSheet.h"


namespace prx {
	
	enum class AnimationState { PLAY, LOOP, STOP };

	class AnimatedSprite : public Sprite {
		PRX_DISALLOW_COPY_AND_MOVE(AnimatedSprite)
	private:
		unsigned int m_AnimationID;
		// Store sprite sheet as dedicate sprite sheet pointer to not cast TextureBase 
		// to the sheet every getUVs call
		SpriteSheet*			m_SpriteSheet;
		mutable AnimationState	m_AnimationState;
		unsigned int			m_DefaultFrame;
	
	public:
		// TODO: setting default frame
		AnimatedSprite(const hpm::vec2& size, SpriteSheet* texture, const std::string& animationName);
		AnimatedSprite(const hpm::vec2& size, SpriteSheet* texture, unsigned int animationID);
		AnimatedSprite(float width, float height, SpriteSheet* texture, unsigned int animationID);
		AnimatedSprite(float width, float height, SpriteSheet* texture, const std::string& animationName);

		void update();
		// Call this after spritesheet initialized
		void init();

		const float* getUVs() const noexcept override;

		void reflect(bool reflect) noexcept override;

		inline void loopAnimation(unsigned int ID) noexcept;
		inline void playAnimation(unsigned int ID) noexcept;
		inline void loopAnimation(const std::string& animationName) noexcept;
		inline void playAnimation(const std::string& animationName) noexcept;
		inline void stopAnimation() noexcept;
		
		inline AnimationState getAnimationState();
	
	private:
		void setDefaultUVs() noexcept override;
		void setReflectDefaultUVs() noexcept override {};
	};

	inline void AnimatedSprite::loopAnimation(unsigned ID) noexcept {
		m_AnimationID = ID;
		m_AnimationState = AnimationState::LOOP;
	}

	inline void AnimatedSprite::loopAnimation(const std::string& animationName) noexcept {
		m_AnimationID = m_SpriteSheet->getAnimationID(animationName);
		m_AnimationState = AnimationState::LOOP;
	}


	inline void AnimatedSprite::playAnimation(unsigned ID) noexcept {
		m_AnimationID = ID;
		m_AnimationState = AnimationState::PLAY;
	}

	inline void AnimatedSprite::playAnimation(const std::string& animationName) noexcept {
		m_AnimationID = m_SpriteSheet->getAnimationID(animationName);
		m_AnimationState = AnimationState::PLAY;
	}


	inline void AnimatedSprite::stopAnimation() noexcept {
		m_AnimationState = AnimationState::STOP;
	}

	inline AnimationState AnimatedSprite::getAnimationState() {
		return m_AnimationState;
	}
}
#endif
