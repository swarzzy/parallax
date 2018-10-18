#include <scene/SpriteNode.h>
#include <renderer/Renderer2D.h>

namespace prx {
	SpriteNode::SpriteNode(float x, float y, float width, float height,
						   unsigned int color, Node* parent)
		: Node(parent, width, height),
		  m_Sprite(new Sprite(width, height, color))
	{
		m_Position.x = x;
		m_Position.y = y;
	}

	SpriteNode::SpriteNode(float x, float y, float width, float height, 
						   TextureBase* texture, Node* parent) 
		: Node(parent, width, height),
		m_Sprite(new Sprite(width, height, texture))
	{
		m_Position.x = x;
		m_Position.y = y;
	}

	SpriteNode::SpriteNode(float width, float height, 
						   unsigned color, Node* parent)
		: Node(parent, width, height),
		m_Sprite(new Sprite(width, height, color))
	{}

	SpriteNode::SpriteNode(float width, float height, 
						   TextureBase* texture, Node* parent)
		: Node(parent, width, height),
		m_Sprite(new Sprite(width, height, texture))
	{}

	SpriteNode::~SpriteNode() {
		delete m_Sprite;
	}

	void SpriteNode::update() {
		if (m_NeedsUpdate) {
			updatePosition();
			forceUpdateChildren();
		}
		else
			updateChildren();
	}

	void SpriteNode::draw(Renderer2D* renderer) {
		m_Sprite->submit(renderer, m_WorldMat * m_AnchorMat, m_Depth);
		drawChildren(renderer);
	}
}