#pragma once

#include "../Common.h"
#include "Node.h"

namespace prx {
	
	class Scene;
	
	class Layer : public Node {
	private:
		PRX_DISALLOW_COPY_AND_MOVE(Layer)

		inline static int MIN_DEPTH_VALUE = -10;
		inline static int MAX_DEPTH_VALUE =  10;

	public:
		static int minDepthValue() noexcept;
		static int maxDepthValue() noexcept;

	private:
		Scene*	m_ParentScene;

	public:
		explicit Layer(int depth, Node* parent = nullptr);
		virtual ~Layer() {};

		void update() override;

		void setDepth(int depth);
	};
}
