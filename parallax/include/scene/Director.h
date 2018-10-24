#pragma once
#include <map>
#include <vector>
#include "../Common.h"
#include <hypermath.h>
#include "../utils/Singleton.h"

namespace prx {

	class Scene;

	enum class SceneState {
		PLAY, STOP
	};

	class Director final : public Singleton<Director>{
	public:
		friend class Singleton<Director>;
	private:
		inline static int MIN_DEPTH_VALUE = -10;
		inline static int MAX_DEPTH_VALUE = 10;

	private:
		std::map<unsigned, Scene*> m_Scenes;
		std::map<std::string, unsigned> m_ScenesList;

		Scene* m_CurrentScene;
		SceneState m_SceneState;
		hpm::vec2 m_CurrentCameraPosition;
		hpm::vec2 m_CurrentCameraViewSpaceSize;

		hpm::vec2 m_ViewportSize;

		Director();
	public:
		static int minDepthValue() noexcept;
		static int maxDepthValue() noexcept;

		PRX_DISALLOW_COPY_AND_MOVE(Director)

		~Director();

		// TODO: checking if window initialized before initialize director
		void update();
		void draw();

		unsigned int createScene(std::string_view name);
		Scene* getScene(std::string_view name);
		Scene* getScene(unsigned ID);

		void setCurrentScene(std::string_view name);
		void setCurrentScene(unsigned ID);

		void initScene();

		inline void playScene() noexcept;
		inline void stopScene() noexcept;

		void setViewport(hpm::vec2 size);
		void updateViewport();
	};

	inline void Director::playScene() noexcept {
		m_SceneState = SceneState::PLAY;
	}

	inline void Director::stopScene() noexcept {
		m_SceneState = SceneState::STOP;
	}


}
