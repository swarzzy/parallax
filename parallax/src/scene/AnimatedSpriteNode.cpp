#include "AnimatedSpriteNode.h"
#include "../renderer/renderable/AnimatedSprite.h"
#include "../textures/SpriteSheet.h"

namespace prx {
	AnimatedSpriteNode::AnimatedSpriteNode(float x, float y, float width, float height,
											ResourceHandler<SpriteSheet> spritesheet, 
											unsigned animationID, Scene* scene, Node* parent)
		: Node(scene, parent, width, height),
		  m_AnimatedSprite(new AnimatedSprite(width, height, spritesheet.get(), animationID)),
		  m_SpriteSheet(spritesheet)
	{
		m_TransformComponent.setPosition(x, y);
		m_TransformComponent.setSize(width, height);

	}

	AnimatedSpriteNode::AnimatedSpriteNode(float x, float y, float width, float height,
		ResourceHandler<SpriteSheet> spritesheet, const std::string& animationName, Scene* scene, Node* parent)
		: Node(scene, parent, width, height),
		m_AnimatedSprite(new AnimatedSprite(width, height, spritesheet.get(), animationName)),
		m_SpriteSheet(spritesheet)
	{
		m_TransformComponent.setPosition(x, y);
		m_TransformComponent.setSize(width, height);

	}

	AnimatedSpriteNode::AnimatedSpriteNode(float width, float height, 
											ResourceHandler<SpriteSheet> spritesheet, 
											unsigned animationID, Scene* scene, Node* parent)
		: Node(scene, parent ,width, height),
		  m_AnimatedSprite(new AnimatedSprite(width, height, spritesheet.get(), animationID)),
		  m_SpriteSheet(spritesheet)
	{
		m_TransformComponent.setSize(width, height);
	}

	AnimatedSpriteNode::AnimatedSpriteNode(float width, float height, ResourceHandler<SpriteSheet> spritesheet,
		const std::string& animationName, Scene* scene, Node* parent)
		: Node(scene, parent, width, height),
		m_AnimatedSprite(new AnimatedSprite(width, height, spritesheet.get(), animationName)),
		m_SpriteSheet(spritesheet)
	{
		m_TransformComponent.setSize(width, height);
	}

	AnimatedSpriteNode::~AnimatedSpriteNode() {
		delete m_AnimatedSprite;
		if (isInitialized()) {
			if (m_SpriteSheet != nullptr)
				m_SpriteSheet->destroy();
		}
	}

	void AnimatedSpriteNode::initInternal() {
		if (m_SpriteSheet != nullptr) {
			m_SpriteSheet->init();
		}
		m_AnimatedSprite->init();
	}

	void AnimatedSpriteNode::updateInternal() {
		m_AnimatedSprite->update();
	}

	void AnimatedSpriteNode::drawInternal() {
		m_AnimatedSprite->submit(getRenderer(), 
								 m_TransformComponent.getWorldMat() * m_TransformComponent.getAnchorMat(), 
								 static_cast<float>(m_Depth));
	}

	void AnimatedSpriteNode::destroyInternal() {
		if (m_SpriteSheet != nullptr) {
			m_SpriteSheet->destroy();
		}
	}
}
