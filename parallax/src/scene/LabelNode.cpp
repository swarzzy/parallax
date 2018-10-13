#include <scene/LabelNode.h>

namespace prx {
	LabelNode::LabelNode(std::string_view text, unsigned color, Renderer2D * renderer, Node * parent)
		: Node(parent, renderer),
		  m_Label(new Label(text, color))
	{
		m_WorldMat = hpm::mat3::identity();
		m_LocalMat = hpm::mat3::translation(0.0f, 0.0f);
	}

	LabelNode::LabelNode(std::string_view text, const Font* font, unsigned color, Renderer2D* renderer, Node* parent)
		: Node(parent, renderer),
		m_Label(new Label(text, font, color))
	{
		m_WorldMat = hpm::mat3::identity();
		m_LocalMat = hpm::mat3::translation(0.0f, 0.0f);
	}

	LabelNode::LabelNode(std::string_view text, float x, float y, unsigned color, Renderer2D* renderer, Node* parent)
		: Node(parent, renderer),
		m_Label(new Label(text, color))
	{
		m_WorldMat = hpm::mat3::identity();
		m_LocalMat = hpm::mat3::translation(x, y);
	}

	LabelNode::LabelNode(std::string_view text, const Font* font, float x, float y, unsigned color,
		Renderer2D* renderer, Node* parent)
		: Node(parent, renderer),
		m_Label(new Label(text, font, color))
	{
		m_WorldMat = hpm::mat3::identity();
		m_LocalMat = hpm::mat3::translation(x, y);
	}

	LabelNode::~LabelNode() {
		delete m_Label;
	}

	void LabelNode::update() {
		if (m_NeedsUpdate) {
			updatePosition();
			forceUpdateChildren();
		}
		else
			updateChildren();
	}

	void LabelNode::draw() {
		m_Label->submit(m_Renderer, m_WorldMat);
		drawChildren();
	}
}

