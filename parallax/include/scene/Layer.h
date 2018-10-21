#pragma once

#include "../Common.h"
#include "Node.h"

namespace prx {
	
	class Scene;
	
	class Layer : public Node {
	private:
		inline static int MIN_DEPTH_VALUE = -10;
		inline static int MAX_DEPTH_VALUE =  10;
		
	public:
		
		PRX_DISALLOW_COPY_AND_MOVE(Layer)
		
		static int minDepthValue() noexcept;
		static int maxDepthValue() noexcept;

	private:
		Scene*	m_ParentScene;

	public:
		explicit Layer(int depth, Scene* parent = nullptr);
		virtual ~Layer() {};

		void update() override;

		void setParent(Scene* parent);

		void setDepth(int depth);

	private:
		inline void setPosition(const hpm::vec2& position) noexcept override final {};
		inline void setPosition(float x, float y) noexcept override final {};
		inline void setScale(float scale) noexcept override final {};
		inline void setRotation(float angle, float radius = 0) noexcept override final {};
		inline void setAnchorPoint(hpm::vec2 anchorPoint) noexcept override final {};
		inline void setAnchorPoint(float x, float y) noexcept override final {};
		inline void setParent(Node* parent) override final {};
	};
}
