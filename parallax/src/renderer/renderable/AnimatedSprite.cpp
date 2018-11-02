#include "AnimatedSprite.h"
#include "../../textures/SpriteSheet.h"

namespace prx {
	AnimatedSprite::AnimatedSprite(const hpm::vec2& size, SpriteSheet* texture, const std::string& animationName) 
		: Sprite(size, texture),
		m_AnimationID(texture->getAnimationID(animationName)),
		m_SpriteSheet(texture),
		m_AnimationState(AnimationState::STOP),
		m_DefaultFrame(0)
	{
		// It`s setting UVs two times, here and in renderable constructor
		setDefaultUVs();
	}

	AnimatedSprite::AnimatedSprite(const hpm::vec2& size, SpriteSheet* texture, unsigned int animationID)
		: Sprite(size, texture),
		m_AnimationID(animationID),
		m_SpriteSheet(texture),
		m_AnimationState(AnimationState::STOP),
		m_DefaultFrame(0)
	{
		// It`s setting UVs two times, here and in renderable constructor
		setDefaultUVs();
	}

	AnimatedSprite::AnimatedSprite(float width, float height, SpriteSheet* texture, unsigned int animationID)
		: Sprite(width, height, texture),
		m_AnimationID(animationID),
		m_SpriteSheet(texture),
		m_AnimationState(AnimationState::STOP),
		m_DefaultFrame(0)
	{}

	AnimatedSprite::AnimatedSprite(float width, float height, SpriteSheet* texture, const std::string& animationName)
		: Sprite(width, height, texture),
		m_AnimationID(texture->getAnimationID(animationName)),
		m_SpriteSheet(texture),
		m_AnimationState(AnimationState::STOP),
		m_DefaultFrame(0)
	{}


	void AnimatedSprite::update() {
		if (m_AnimationState != AnimationState::STOP) {
			if (m_AnimationState == AnimationState::LOOP) {
				const UV* tc = m_SpriteSheet->getTexCoords(m_AnimationID);

				m_UVs[0] = tc->lbX;
				m_UVs[1] = tc->lbY;
				m_UVs[2] = tc->ltX;
				m_UVs[3] = tc->ltY;
				m_UVs[4] = tc->rtX;
				m_UVs[5] = tc->rtY;
				m_UVs[6] = tc->rbX;
				m_UVs[7] = tc->rbY;

			}
			else
				if (m_AnimationState == AnimationState::PLAY) {
					if (m_SpriteSheet->getAnimationCurrentFrame(m_AnimationID)
						< m_SpriteSheet->getAnimaionFrameCount(m_AnimationID) - 1) {

						const UV* tc = m_SpriteSheet->getTexCoords(m_AnimationID);

						m_UVs[0] = tc->lbX;
						m_UVs[1] = tc->lbY;
						m_UVs[2] = tc->ltX;
						m_UVs[3] = tc->ltY;
						m_UVs[4] = tc->rtX;
						m_UVs[5] = tc->rtY;
						m_UVs[6] = tc->rbX;
						m_UVs[7] = tc->rbY;
					}
					else {
						m_AnimationState = AnimationState::STOP;
						m_SpriteSheet->resetAnimations();
					}
				}
		}
	}

	void AnimatedSprite::init() {
		setDefaultUVs();
	}

	void AnimatedSprite::reflect(bool reflect) noexcept {
		m_SpriteSheet->reflect(reflect);
	}

	const float* AnimatedSprite::getUVs() const noexcept {
		return m_UVs;
	};

	void AnimatedSprite::setDefaultUVs() noexcept {
		const UV* tc = m_SpriteSheet->getFrameUVs(m_DefaultFrame);

		m_UVs[0] = tc->lbX;
		m_UVs[1] = tc->lbY;
		m_UVs[2] = tc->ltX;
		m_UVs[3] = tc->ltY;
		m_UVs[4] = tc->rtX;
		m_UVs[5] = tc->rtY;
		m_UVs[6] = tc->rbX;
		m_UVs[7] = tc->rbY;
	}

	void AnimatedSprite::loopAnimation(unsigned ID) noexcept {
		m_AnimationID = ID;
		m_AnimationState = AnimationState::LOOP;
	}

	void AnimatedSprite::loopAnimation(const std::string& animationName) noexcept {
		m_AnimationID = m_SpriteSheet->getAnimationID(animationName);
		m_AnimationState = AnimationState::LOOP;
	}


	void AnimatedSprite::playAnimation(unsigned ID) noexcept {
		m_AnimationID = ID;
		m_AnimationState = AnimationState::PLAY;
	}

	void AnimatedSprite::playAnimation(const std::string& animationName) noexcept {
		m_AnimationID = m_SpriteSheet->getAnimationID(animationName);
		m_AnimationState = AnimationState::PLAY;
	}


	void AnimatedSprite::stopAnimation() noexcept {
		m_AnimationState = AnimationState::STOP;
	}
}