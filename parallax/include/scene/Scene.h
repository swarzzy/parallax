#pragma once

#include "Node.h"

namespace prx {

	class Camera2D;

	class Scene : public Node {
	protected:
		Renderer2D* m_Renderer;
		Camera2D*	m_Camera;
		bool		m_CameraMoved;
	public:
		explicit Scene(Renderer2D* renderer, Node* parent = nullptr);
		~Scene();

		void init() override;
		void update() override;
		void draw(Renderer2D* renderer) override;
		void present();

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
