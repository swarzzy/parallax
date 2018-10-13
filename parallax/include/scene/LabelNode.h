#pragma once
#include "../renderer/renderable/Renderable2D.h"
#include "../renderer/renderable/Label.h"
#include "Node.h"

namespace prx {
	class LabelNode final : public Node {
	private:
		Label* m_Label;
	public:
		LabelNode(std::string_view text, unsigned color, Renderer2D* renderer, Node* parent = nullptr);
		LabelNode(std::string_view text, const Font* font, unsigned color, Renderer2D* renderer, Node* parent = nullptr);
		LabelNode(std::string_view text, float x, float y, unsigned color, Renderer2D* renderer, Node* parent = nullptr);
		LabelNode(std::string_view text, const Font* font, float x, float y, unsigned color, Renderer2D* renderer, Node* parent = nullptr);

		~LabelNode();

		void update() override;
		void draw() override;

		inline Label& getLabel() const noexcept;

	public:
		LabelNode(const LabelNode& other) = delete;
		LabelNode(const LabelNode&& other) = delete;
		LabelNode(LabelNode&& other) = delete;
		LabelNode& operator=(const LabelNode& other) = delete;
		LabelNode& operator=(const LabelNode&& other) = delete;
		LabelNode& operator=(LabelNode&& other) = delete;
	};

	inline Label& LabelNode::getLabel() const noexcept {
		return *m_Label;
	}

}
