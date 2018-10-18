#pragma once
#include "Node.h"
#include "../renderer/renderable/AnimatedSprite.h"

namespace prx {
	
	class SpriteSheet;
	
	class AnimatedSpriteNode final : public Node {
	private:
		AnimatedSprite* m_AnimatedSprite;

	public:
		AnimatedSpriteNode(float x, float y,
						   float width, float height,
						   SpriteSheet* texture,
						   unsigned animationID = 0,
						   Node* parent = nullptr);

		AnimatedSpriteNode(float width, float height,
						   SpriteSheet* texture,
						   unsigned animationID = 0,
						   Node* parent = nullptr);

		~AnimatedSpriteNode();

		void update() override;
		void draw(Renderer2D* renderer) override;

		inline void reflect(bool reflect) noexcept;

		inline void loopAnimation(unsigned int ID) noexcept;
		inline void playAnimation(unsigned int ID) noexcept;
		inline void stopAnimation() noexcept;

	public:
		AnimatedSpriteNode(const AnimatedSpriteNode& other) = delete;
		AnimatedSpriteNode(const AnimatedSpriteNode&& other) = delete;
		AnimatedSpriteNode(AnimatedSpriteNode&& other) = delete;
		AnimatedSpriteNode& operator=(const AnimatedSpriteNode& other) = delete;
		AnimatedSpriteNode& operator=(const AnimatedSpriteNode&& other) = delete;
		AnimatedSpriteNode& operator=(AnimatedSpriteNode&& other) = delete;
	};

	inline void AnimatedSpriteNode::reflect(bool reflect) noexcept {
		m_AnimatedSprite->reflect(reflect);
	}

	inline void AnimatedSpriteNode::loopAnimation(unsigned ID) noexcept {
		m_AnimatedSprite->loopAnimation(ID);
	}

	inline void AnimatedSpriteNode::playAnimation(unsigned ID) noexcept {
		m_AnimatedSprite->playAnimation(ID);
	}

	inline void AnimatedSpriteNode::stopAnimation() noexcept {
		m_AnimatedSprite->stopAnimation();
	}




}
