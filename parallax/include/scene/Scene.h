#pragma once

#include "Node.h"

namespace prx {

	class Layer;
	class Camera2D;

	class Scene : public Node {
	public:
		inline static hpm::vec2 defaultCameraPosition = hpm::vec2(0.0);
	private:
		inline static auto sortingPredicate = [](Node* a, Node* b){return a->getDepth() < b->getDepth(); };
	protected:
		Renderer2D* m_Renderer;
		Camera2D*	m_Camera;
		bool		m_CameraMoved;
		bool		m_NeedsSorting;
		
		std::vector<Layer*> m_Layers;
	public:
		// Scenes now can not be children but the still be derived from Node
		explicit Scene(Renderer2D* renderer);
		~Scene();

		void init() override;
		void update() override;
		void sortChildren();
		void draw(Renderer2D* renderer) override;
		void present();
		
		void sortRequest() noexcept;

		void setCameraPosition(hpm::vec2 position) noexcept;
		void setCameraPosition(float x, float y) noexcept;

	public:
		Scene(const Scene& other) = delete;
		Scene(const Scene&& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(const Scene&& other) = delete;
		Scene& operator=(Scene&& other) = delete;
	};
}
