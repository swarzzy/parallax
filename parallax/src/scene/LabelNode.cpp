#include <scene/LabelNode.h>

namespace prx {
	LabelNode::LabelNode(Scene* scene, std::string_view text, unsigned color, Node * parent)
		: Node(scene, parent),
		  m_Label(new Label(text, color))
	{}

	LabelNode::LabelNode(Scene* scene, std::string_view text, const Font* font, unsigned color, Node* parent)
		: Node(scene, parent),
		m_Label(new Label(text, font, color))
	{}

	LabelNode::LabelNode(Scene* scene, std::string_view text, float x, float y, unsigned color, Node* parent)
		: Node(scene, parent),
		m_Label(new Label(text, color))
	{
		m_TransformComponent.setPosition(x, y);
	}

	LabelNode::LabelNode(Scene* scene, std::string_view text, const Font* font, float x, float y, unsigned color, Node* parent)
		: Node(scene, parent),
		m_Label(new Label(text, font, color))
	{
		m_TransformComponent.setPosition(x, y);
	}

	LabelNode::~LabelNode() {
		delete m_Label;
	}

	void LabelNode::drawInternal(Renderer2D* renderer) {
		m_Label->submit(renderer, m_TransformComponent.getWorldMat() , m_Depth);
	}
}

