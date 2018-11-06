#pragma once

#include "../Common.h"
#include "Node.h"

namespace prx {
	
	class Scene;
	
	class Layer : public Node {
		PRX_DISALLOW_COPY_AND_MOVE(Layer)
	private:
		Scene*	m_ParentScene;

	public:
		Layer(Scene* scene, int depth);
		virtual ~Layer() {};

		void update() override final;

		void setDepth(int depth);

		friend class Scene;

	private:
		inline void setPosition(const hpm::vec2& position) noexcept override final {};
		inline void setPosition(float x, float y) noexcept override final {};
		inline void setScale(float scale) noexcept override final {};
		inline void setSize(float width, float height) noexcept override final {};
		inline void setSize(const hpm::vec2& size) noexcept override final {};
		inline void setRotation(float angle, float radius = 0) noexcept override final {};
		inline void setAnchorPoint(hpm::vec2 anchorPoint) noexcept override final {};
		inline void setAnchorPoint(float x, float y) noexcept override final {};
		inline void setParent(Node* parent) override final {};
		inline void setColor(unsigned color) noexcept override {};

		inline void enableVisibilityTest(bool enable) noexcept override final {};
		inline void setVisibilityTestMode(VisibilityTestMode mode) noexcept override final {};
	};
}
