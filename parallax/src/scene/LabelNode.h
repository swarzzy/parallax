#pragma once
#include "../renderer/renderable/Label.h"
#include "Node.h"
#include "../Common.h"

namespace prx {
	class LabelNode final : public Node {
	PRX_DISALLOW_COPY_AND_MOVE(LabelNode)
	private:
		Label* m_Label;

	public:
		LabelNode(Scene* scene, std::string_view text, unsigned color, Node* parent = nullptr);
		LabelNode(Scene* scene, std::string_view text, const Font* font, unsigned color, Node* parent = nullptr);
		LabelNode(Scene* scene, std::string_view text, float x, float y, unsigned color, Node* parent = nullptr);
		LabelNode(Scene* scene, std::string_view text, const Font* font, float x, float y, unsigned color, Node* parent = nullptr);

		void drawInternal() override;

		~LabelNode();

		inline Label& getLabel() const noexcept;

		inline void setColor(unsigned color) noexcept override;
		inline void setFont(const Font* font) noexcept;
	};

	inline Label& LabelNode::getLabel() const noexcept {
		return *m_Label;
	}

	inline void LabelNode::setColor(unsigned color) noexcept {
		m_Label->setColor(color);
	}

	inline void LabelNode::setFont(const Font* font) noexcept {
		m_Label->setFont(font);
	}
}
