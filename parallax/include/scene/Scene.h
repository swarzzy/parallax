#pragma once

#include <functional>
#include "Node.h"
#include "../Common.h"

namespace prx {

	class Layer;
	class Camera2D;

	class Scene : public Node {
	private:
		inline static const hpm::vec2 DEFAULT_CAMERA_POSITION = hpm::vec2(0.0);
		inline static const std::function<bool(Node*,Node*)> SORT_PREDICATE = 
			[](Node* a, Node* b){return a->getDepth() < b->getDepth(); };

	public:
		inline static hpm::vec2 defaultCameraPosition() noexcept;

	protected:

		PRX_DISALLOW_COPY_AND_MOVE(Scene)

		Renderer2D* m_Renderer;
		Camera2D*	m_Camera;
		bool		m_CameraMoved;
		bool		m_NeedsSorting;
		
	public:
		explicit Scene(Renderer2D* renderer);
		~Scene();

		void sortChildren();
		void present();
		
		void sortRequest() noexcept;

		void setCameraPosition(hpm::vec2 position) noexcept;
		void setCameraPosition(float x, float y) noexcept;

	protected:
		inline void initInternal() override;
		inline void updateInternal() override;

	private:
		void setParent(Node* parent) override {};
	};

	inline hpm::vec2 Scene::defaultCameraPosition() noexcept {
		return DEFAULT_CAMERA_POSITION;
	}

}
