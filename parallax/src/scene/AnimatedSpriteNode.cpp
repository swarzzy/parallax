#include <scene/AnimatedSpriteNode.h>
#include <renderer/renderable/AnimatedSprite.h>

namespace prx {
	AnimatedSpriteNode::AnimatedSpriteNode(float x, float y, float width, float height,
											SpriteSheet* texture, unsigned animationID, Node* parent)
		: Node(parent, width, height),
		  m_AnimatedSprite(new AnimatedSprite(width, height, texture, animationID)) 
	{
		m_TransformComponent.setPosition(x, y);
		m_TransformComponent.setSize(width, height);

	}

	AnimatedSpriteNode::AnimatedSpriteNode(float width, float height, 
											SpriteSheet* texture, unsigned animationID,	Node* parent) 
		: Node(parent ,width, height),
		  m_AnimatedSprite(new AnimatedSprite(width, height, texture, animationID)) 
	{
		m_TransformComponent.setSize(width, height);
	}

	AnimatedSpriteNode::~AnimatedSpriteNode() {
		
	}

	void AnimatedSpriteNode::drawInternal(Renderer2D* renderer) {
		m_AnimatedSprite->submit(renderer, m_TransformComponent.getWorldMat() * m_TransformComponent.getAnchorMat(), m_Depth);
	}
}