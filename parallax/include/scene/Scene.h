#pragma once

#include "Node.h"

namespace prx {

	class Scene : public Node {
	protected:
	public:
		explicit Scene(Renderer2D* renderer, Node* parent = nullptr);
		~Scene();

		void init() override;
		void update() override;
		void draw() override;

	public:
		Scene(const Scene& other) = delete;
		Scene(const Scene&& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(const Scene&& other) = delete;
		Scene& operator=(Scene&& other) = delete;
	};
}
