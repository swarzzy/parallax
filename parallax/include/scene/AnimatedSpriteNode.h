#pragma once
#include "Node.h"
#include "../renderer/renderable/AnimatedSprite.h"
#include "../resources/ResourceHandler.h"

namespace prx {
	
	class SpriteSheet;
	
	class AnimatedSpriteNode final : public Node {
	private:
		AnimatedSprite* m_AnimatedSprite;
		ResourceHandler<SpriteSheet> m_SpriteSheet;

	public:
		AnimatedSpriteNode(float x, float y,
						   float width, float height,
						   ResourceHandler<SpriteSheet> spritesheet,
						   unsigned animationID,
						   Scene* scene,
						   Node* parent = nullptr);

		AnimatedSpriteNode(float x, float y,
						   float width, float height,
						   ResourceHandler<SpriteSheet> spritesheet,
						   const std::string& animationName,
						   Scene* scene,
						   Node* parent = nullptr);

		AnimatedSpriteNode(float width, float height,
						   ResourceHandler<SpriteSheet> spritesheet,
						   unsigned animationID,
						   Scene* scene,
						   Node* parent = nullptr);
		
		AnimatedSpriteNode(float width, float height,
						   ResourceHandler<SpriteSheet> spritesheet,
						   const std::string& animationName,
						   Scene* scene,
						   Node* parent = nullptr);

		~AnimatedSpriteNode();

		inline void reflect(bool reflect) noexcept;

		inline void loopAnimation(unsigned int ID) noexcept;
		inline void playAnimation(unsigned int ID) noexcept;
		inline void loopAnimation(const std::string& name) noexcept;
		inline void playAnimation(const std::string& name) noexcept;
		inline void stopAnimation() noexcept;

	private:
		void initInternal() override;
		void updateInternal() override;
		void drawInternal() override;
		void destroyInternal() override;

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

	inline void AnimatedSpriteNode::loopAnimation(const std::string& name) noexcept {
		m_AnimatedSprite->loopAnimation(name);
	}


	inline void AnimatedSpriteNode::playAnimation(unsigned ID) noexcept {
		m_AnimatedSprite->playAnimation(ID);
	}

	inline void AnimatedSpriteNode::playAnimation(const std::string& name) noexcept {
		m_AnimatedSprite->playAnimation(name);
	}

	inline void AnimatedSpriteNode::stopAnimation() noexcept {
		m_AnimatedSprite->stopAnimation();
	}




}
