#include <scene/SpriteNode.h>
#include <renderer/Renderer2D.h>

namespace prx {
	SpriteNode::SpriteNode(float x, float y, float depth, float width, float height,
						   unsigned int color, Renderer2D* renderer, Node* parent)
		: Node(parent, renderer),
		  m_Sprite(new Sprite(width, height, color))
	{
		m_LocalMat = hpm::mat3::translation(x, y);
	}

	SpriteNode::SpriteNode(float x, float y, float depth, float width, float height, 
						   TextureBase* texture, Renderer2D* renderer, Node* parent) 
		: Node(parent, renderer),
		m_Sprite(new Sprite(width, height, texture))
	{
		m_LocalMat = hpm::mat3::translation(x, y);
	}

	SpriteNode::SpriteNode(float depth, float width, float height, 
						   unsigned color, Renderer2D* renderer, Node* parent)
		: Node(parent, renderer),
		m_Sprite(new Sprite(width, height, color))
	{
		m_LocalMat = hpm::mat3::translation(0.0f, 0.0f);
	}

	SpriteNode::SpriteNode(float depth, float width, float height, 
						   TextureBase* texture, Renderer2D* renderer, Node* parent)
		: Node(parent, renderer),
		m_Sprite(new Sprite(width, height, texture))
	{
		m_LocalMat = hpm::mat3::translation(0.0f, 0.0f);
	}

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

	void SpriteNode::draw() {
		m_Renderer->drawRect(m_WorldMat, m_Sprite->getSize().x, m_Sprite->getSize().y, m_Sprite->getTexture());
		drawChildren();
	}
}