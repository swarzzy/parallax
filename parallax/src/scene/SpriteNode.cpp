#include <scene/SpriteNode.h>

namespace prx {
	SpriteNode::SpriteNode(float x, float y, float depth, float width, float height,
						   unsigned int color, Renderer2D* renderer, Node* parent)
		: Node(parent, renderer),
		  m_Group(new Group(hpm::mat4::identity()))
	{
		m_Group->add(new Sprite(0, 0, depth, width, height, color));
		m_LocalMat = hpm::mat4::translation(hpm::vec3(x, y, depth));
	}

	SpriteNode::SpriteNode(float x, float y, float depth, float width, float height, 
						   TextureBase* texture, Renderer2D* renderer, Node* parent) 
		: Node(parent, renderer),
		m_Group(new Group(hpm::mat4::identity()))
	{
		m_Group->add(new Sprite(0, 0, depth, width, height, texture));
		m_LocalMat = hpm::mat4::translation(hpm::vec3(x, y, depth));
	}

	SpriteNode::SpriteNode(float depth, float width, float height, 
						   unsigned color, Renderer2D* renderer, Node* parent)
		: Node(parent, renderer),
		m_Group(new Group(hpm::mat4::identity()))
	{
		m_Group->add(new Sprite(0, 0, depth, width, height, color));
		m_LocalMat = hpm::mat4::translation(hpm::vec3(0, 0, depth));
	}

	SpriteNode::SpriteNode(float depth, float width, float height, 
						   TextureBase* texture, Renderer2D* renderer, Node* parent)
		: Node(parent, renderer),
		m_Group(new Group(hpm::mat4::identity()))
	{
		m_Group->add(new Sprite(0, 0, depth, width, height, texture));
		m_LocalMat = hpm::mat4::translation(hpm::vec3(0, 0, depth));
	}

	SpriteNode::~SpriteNode() {
		delete m_Group;
	}

	void SpriteNode::update() {
		if (m_NeedsUpdate) {
			updatePosition();
			forceUpdateChildren();
			m_Group->setTransformationMatrix(m_WorldMat);
		}
		else
			updateChildren();
	}

	void SpriteNode::draw() {
		m_Group->submit(m_Renderer);
		drawChildren();
	}
}