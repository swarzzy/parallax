#pragma once

#include "Node.h"

namespace prx {
	
	class Scene;
	
	class Layer : public Node {
	public:
		inline static int minDepthValue = -10;
		inline static int maxDepthValue =  10;

	private:
		Scene*	m_ParentScene;
		bool	m_DepthUpdated;

	public:
		explicit Layer(int depth, Node* parent = nullptr);
		~Layer() {};

		void init() override;
		void update() override;
		void draw(Renderer2D* renderer) override;

		void setDepth(int depth);

	public:
		Layer(const Layer& other) = delete;
		Layer(const Layer&& other) = delete;
		Layer(Layer&& other) = delete;
		Layer& operator=(const Layer& other) = delete;
		Layer& operator=(const Layer&& other) = delete;
		Layer& operator=(Layer&& other) = delete;
	};
}
