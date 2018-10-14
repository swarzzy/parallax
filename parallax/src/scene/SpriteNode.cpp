#include <scene/SpriteNode.h>
#include <renderer/Renderer2D.h>

namespace prx {
	SpriteNode::SpriteNode(float x, float y, int depth, float width, float height,
						   unsigned int color, Node* parent)
		: Node(parent),
		  m_Sprite(new Sprite(width, height, color))
	{
		m_WorldMat = hpm::mat3::identity();
		m_LocalMat = hpm::mat3::translation(x, y);
	}

	SpriteNode::SpriteNode(float x, float y, int depth, float width, float height, 
						   TextureBase* texture, Node* parent) 
		: Node(parent),
		m_Sprite(new Sprite(width, height, texture))
	{
		m_WorldMat = hpm::mat3::identity();
		m_LocalMat = hpm::mat3::translation(x, y);
	}

	SpriteNode::SpriteNode(int depth, float width, float height, 
						   unsigned color, Node* parent)
		: Node(parent),
		m_Sprite(new Sprite(width, height, color))
	{
		m_WorldMat = hpm::mat3::identity();
		m_LocalMat = hpm::mat3::translation(0.0f, 0.0f);
	}

	SpriteNode::SpriteNode(int depth, float width, float height, 
						   TextureBase* texture, Node* parent)
		: Node(parent),
		m_Sprite(new Sprite(width, height, texture))
	{
		m_WorldMat = hpm::mat3::identity();
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

	void SpriteNode::draw(Renderer2D* renderer) {
		m_Sprite->submit(renderer, m_WorldMat);
		drawChildren(renderer);
	}
}