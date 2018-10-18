#include <scene/AnimatedSpriteNode.h>
#include <renderer/renderable/AnimatedSprite.h>

namespace prx {
	AnimatedSpriteNode::AnimatedSpriteNode(float x, float y, float width, float height,
											SpriteSheet* texture, unsigned animationID, Node* parent)
		: Node(parent, width, height),
		  m_AnimatedSprite(new AnimatedSprite(width, height, texture, animationID)) 
	{
		m_Position.x = x;
		m_Position.y = y;
	}

	AnimatedSpriteNode::AnimatedSpriteNode(float width, float height, 
											SpriteSheet* texture, unsigned animationID,	Node* parent) 
		: Node(parent ,width, height),
		  m_AnimatedSprite(new AnimatedSprite(width, height, texture, animationID))
	{}

	AnimatedSpriteNode::~AnimatedSpriteNode() {
		
	}

	void AnimatedSpriteNode::update() {
		if (m_NeedsUpdate) {
			updatePosition();
			forceUpdateChildren();
		}
		else
			updateChildren();
	}

	void AnimatedSpriteNode::draw(Renderer2D* renderer) {
		m_AnimatedSprite->submit(renderer, m_WorldMat * m_AnchorMat, m_Depth);
		drawChildren(renderer);
	}
}
