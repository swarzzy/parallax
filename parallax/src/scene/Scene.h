#pragma once

#include <functional>
#include "Node.h"
#include "../Common.h"
#include "../resources/ResourceHandler.h"
#include "Group.h"

namespace prx {

	class Layer;
	class Camera2D;
	class SpriteNode;
	class LabelNode;
	class AnimatedSpriteNode;

	void delete_node(Node* node);

	class Scene {
		PRX_DISALLOW_COPY_AND_MOVE(Scene)
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
		friend class Node;

	protected:

		unsigned int		m_ID;
		std::string			m_Name;
		std::vector<Layer*> m_Layers;
		Renderer2D*			m_Renderer;
		Camera2D*			m_Camera;
		bool				m_CameraMoved;
		bool				m_NeedsSorting;
		bool				m_Initialized;
		
	public:
		// Scene now doesn`t know that renderer is singleton so passing it every renderer we need
		Scene(std::string_view name, Renderer2D* renderer);
		~Scene();

		static const hpm::vec2& getCurrentCameraPosition() { return currentCameraPosition; };
		static const hpm::vec2& getCurrentCameraViewSize() { return currentViewSize; };

		SpriteNode* createSprite(float width, float height, std::string_view texturePath, Node* parent = nullptr);
		SpriteNode* createSprite(float width, float height, unsigned color, Node* parent = nullptr);

		AnimatedSpriteNode* createAnimation(float width, float height, std::string_view spritesheetPath, std::string_view startAnimation, Node* parent = nullptr);

		Group* createGroup(Node* parent = nullptr);

		LabelNode* createLabel(std::string_view text, unsigned int color, Node* parent = nullptr);
		LabelNode* createLabel(std::string_view text, Font* font, unsigned int color, Node* parent = nullptr);

		Layer* createLayer(int depth);

		void sortChildren();
		void init();
		void update();
		void draw();
		void destroy();

		void removeChild(Layer* layer);
		
		void sortRequest() noexcept;

		void setCameraPosition(hpm::vec2 position) noexcept;
		void setCameraPosition(float x, float y) noexcept;

		void setCameraViewSpaceSize(hpm::vec2 size) noexcept;
		void setCameraViewSpaceSize(float x, float y) noexcept;

		void setRenderer(Renderer2D* renderer) noexcept;

		const hpm::vec2& getCameraPosition() const noexcept;
		const Camera2D& getCamera() const noexcept;
		const hpm::vec2& getViewSize() const noexcept;
		inline unsigned getID() const noexcept;
		inline const std::string& getName() const noexcept;
		inline bool isInitialized() const noexcept;
		inline Renderer2D* getRenderer() const;

	private:
		void addChild(Layer* child);

	};

	inline hpm::vec2 Scene::defaultCameraPosition() noexcept {
		return DEFAULT_CAMERA_POSITION;
	}

	inline unsigned Scene::getID() const noexcept {
		return m_ID;
	}

	inline const std::string& Scene::getName() const noexcept {
		return m_Name;
	}


	inline bool Scene::isInitialized() const noexcept {
		return m_Initialized;
	}

	inline Renderer2D* Scene::getRenderer() const {
		return m_Renderer;
	}
}