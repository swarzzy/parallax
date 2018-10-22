#pragma once

#include <functional>
#include "Node.h"
#include "../Common.h"

namespace prx {

	class Layer;
	class Camera2D;

	class Scene {
	private:
		inline static const hpm::vec2 DEFAULT_CAMERA_POSITION = hpm::vec2(0.0);
		static const std::function<bool(Layer*, Layer*)> SORT_PREDICATE;

		inline static unsigned int GLOBAL_SCENE_COUNTER = 0;

		// Temporary solution
		inline static hpm::vec2 currentCameraPosition = hpm::vec2(0.0);
		inline static hpm::vec2 currentViewSize = hpm::vec2(0.0);


	public:
		inline static hpm::vec2 defaultCameraPosition() noexcept;

		friend class Layer;

	protected:

		PRX_DISALLOW_COPY_AND_MOVE(Scene)

		unsigned int		m_ID;
		std::string			m_Name;
		std::vector<Layer*> m_Layers;
		Renderer2D*			m_Renderer;
		Camera2D*			m_Camera;
		bool				m_CameraMoved;
		bool				m_NeedsSorting;
		
	public:
		Scene(std::string_view name, Renderer2D* renderer);
		~Scene();

		static const hpm::vec2& getCurrentCameraPosition() { return currentCameraPosition; };
		static const hpm::vec2& getCurrentCameraViewSize() { return currentViewSize; };

		void sortChildren();
		void init();
		void update();
		void draw();
		void destroy() {};

		void removeChild(Layer* layer);
		
		void sortRequest() noexcept;

		void setCameraPosition(hpm::vec2 position) noexcept;
		void setCameraPosition(float x, float y) noexcept;

		void setCameraViewSpaceSize(hpm::vec2 size) noexcept;
		void setCameraViewSpaceSize(float x, float y) noexcept;

		const hpm::vec2& getCameraPosition() const noexcept;
		const hpm::vec2& getViewSize() const noexcept;
		inline unsigned getID() const noexcept;

	private:
		void addChild(Layer* child);
	};

	inline hpm::vec2 Scene::defaultCameraPosition() noexcept {
		return DEFAULT_CAMERA_POSITION;
	}

	inline unsigned Scene::getID() const noexcept {
		return m_ID;
	}


}
