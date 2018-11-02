#pragma once
#include <map>
#include "../Common.h"
#include <hypermath.h>
#include "../utils/Singleton.h"
#include "../renderer/ForwardRenderer2D.h"

namespace prx {

	class Scene;

	enum class SceneState {
		PLAY, STOP
	};

	class Director final : public Singleton<Director>{
		PRX_DISALLOW_COPY_AND_MOVE(Director)
	public:
		friend class Singleton<Director>;

	private:
		inline static int MIN_DEPTH_VALUE = -10;
		inline static int MAX_DEPTH_VALUE = 10;

	private:
		std::map<unsigned, Scene*> m_Scenes;
		std::map<std::string, unsigned> m_ScenesList;

		Scene*		m_CurrentScene;
		SceneState	m_SceneState;

		hpm::vec2	m_CurrentCameraPosition;
		hpm::vec2	m_CurrentCameraViewSpaceSize;

		hpm::vec2	m_ViewportSize;

		ForwardRenderer2D* m_Renderer;

		Director();
	public:
		static int minDepthValue() noexcept;
		static int maxDepthValue() noexcept;

		~Director();

		void update();
		void render();

		unsigned int createScene(std::string_view name);
		Scene* getScene(std::string_view name);
		Scene* getScene(unsigned ID);

		void setCurrentScene(std::string_view name);
		void setCurrentScene(unsigned ID);

		void initScene();
		void destroyScene();
		void deleteScene(std::string_view name);
		void deleteScene(unsigned ID);

		void playScene() noexcept;
		void stopScene() noexcept;

		void setViewport(hpm::vec2 size);
		void updateViewport();
	};
}