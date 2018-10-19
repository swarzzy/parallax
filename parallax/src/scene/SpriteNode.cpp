#include <scene/SpriteNode.h>
#include <renderer/Renderer2D.h>

namespace prx {
	SpriteNode::SpriteNode(float x, float y, float width, float height,
						   unsigned int color, Node* parent)
		: Node(parent, width, height),
		  m_Sprite(new Sprite(width, height, color))
	{
		m_TransformComponent.setPosition(x, y);
		m_TransformComponent.setSize(width, height);
	}

	SpriteNode::SpriteNode(float x, float y, float width, float height, 
						   TextureBase* texture, Node* parent) 
		: Node(parent, width, height),
		m_Sprite(new Sprite(width, height, texture))
	{
		m_TransformComponent.setPosition(x, y);
		m_TransformComponent.setSize(width, height);

	}

	SpriteNode::SpriteNode(float width, float height, 
						   unsigned color, Node* parent)
		: Node(parent, width, height),
		m_Sprite(new Sprite(width, height, color)) 
	{
		m_TransformComponent.setSize(width, height);
	}

	SpriteNode::SpriteNode(float width, float height, 
						   TextureBase* texture, Node* parent)
		: Node(parent, width, height),
		m_Sprite(new Sprite(width, height, texture)) 
	{
		m_TransformComponent.setSize(width, height);
	}

	SpriteNode::~SpriteNode() {
		delete m_Sprite;
	}

	void SpriteNode::drawInternal(Renderer2D* renderer) {
		m_Sprite->submit(renderer, m_TransformComponent.getWorldMat() * m_TransformComponent.getAnchorMat(), m_Depth);
	}
}