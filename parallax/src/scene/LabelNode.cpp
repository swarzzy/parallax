#include <scene/LabelNode.h>

namespace prx {
	LabelNode::LabelNode(std::string_view text, unsigned color, Node * parent)
		: Node(parent),
		  m_Label(new Label(text, color))
	{
		m_WorldMat = hpm::mat3::identity();
		m_LocalMat = hpm::mat3::translation(0.0f, 0.0f);
	}

	LabelNode::LabelNode(std::string_view text, const Font* font, unsigned color, Node* parent)
		: Node(parent),
		m_Label(new Label(text, font, color))
	{
		m_WorldMat = hpm::mat3::identity();
		m_LocalMat = hpm::mat3::translation(0.0f, 0.0f);
	}

	LabelNode::LabelNode(std::string_view text, float x, float y, unsigned color, Node* parent)
		: Node(parent),
		m_Label(new Label(text, color))
	{
		m_WorldMat = hpm::mat3::identity();
		m_LocalMat = hpm::mat3::translation(x, y);
	}

	LabelNode::LabelNode(std::string_view text, const Font* font, float x, float y, unsigned color, Node* parent)
		: Node(parent),
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

	void LabelNode::draw(Renderer2D* renderer) {
		m_Label->submit(renderer, m_WorldMat);
		drawChildren(renderer);
	}
}

