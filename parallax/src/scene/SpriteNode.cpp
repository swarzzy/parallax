#include "SpriteNode.h"
#include "../renderer/Renderer2D.h"
#include "../resources/ResourceHandler.h"
#include "../scene/Scene.h"

namespace prx {
	SpriteNode::SpriteNode(float x, float y, float width, float height,
						   unsigned int color, Scene* scene, Node* parent)
		: Node(scene, parent, width, height),
		  m_Sprite(new Sprite(width, height, color)),
		  m_Texture(nullptr),
		  m_NormalMap(nullptr)
	{
		m_TransformComponent.setPosition(x, y);
		m_TransformComponent.setSize(width, height);
	}

	SpriteNode::SpriteNode(float x, float y, float width, float height, 
							ResourceHandler<Texture> texture, Scene* scene, Node* parent)
		: Node(scene, parent, width, height),
		  m_Sprite(new Sprite(width, height, texture.get())),
		  m_Texture(texture),
		  m_NormalMap(nullptr)
	{
		m_TransformComponent.setPosition(x, y);
		m_TransformComponent.setSize(width, height);
	}

	SpriteNode::SpriteNode(float width, float height, 
						   unsigned color, Scene* scene, Node* parent)
		: Node(scene, parent, width, height),
		m_Sprite(new Sprite(width, height, color)),
		m_Texture(nullptr),
		m_NormalMap(nullptr)
	{
		m_TransformComponent.setSize(width, height);
	}

	SpriteNode::SpriteNode(float width, float height, 
							ResourceHandler<Texture> texture, Scene* scene, Node* parent)
		: Node(scene, parent, width, height),
		m_Sprite(new Sprite(width, height, texture.get())),
		m_Texture(texture),
		m_NormalMap(nullptr)
	{
		m_TransformComponent.setSize(width, height);
	}

	SpriteNode::SpriteNode(float width, float height, ResourceHandler<Texture> texture,
							ResourceHandler<Texture> normalMap, Scene* scene, Node* parent)
		: Node(scene, parent, width, height),
		m_Sprite(new Sprite(width, height, texture.get(), normalMap.get())),
		m_Texture(texture),
		m_NormalMap(normalMap)
	{
		m_TransformComponent.setSize(width, height);
	}

	SpriteNode::~SpriteNode() {
		delete m_Sprite;
		if (m_Initialized) {
			if (m_Texture != nullptr)
				m_Texture->destroy();
		}
	}

	void SpriteNode::initInternal() {
		if (m_Texture != nullptr) {
			m_Texture->init();
		}
	}

	void SpriteNode::drawInternal() {
		m_Sprite->submit(getRenderer(), 
						 m_TransformComponent.getWorldMat() * m_TransformComponent.getAnchorMat(), 
						 static_cast<float>(m_Depth));
	}

	void SpriteNode::destroyInternal() {
		if (m_Texture != nullptr) {
			m_Texture->destroy();
		}
	}
}
