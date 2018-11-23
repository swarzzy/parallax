#pragma once
#include <map>
#include "../Common.h"
#include <hypermath.h>
#include "../utils/Singleton.h"
#include "../renderer/ForwardRenderer2D.h"
#include "../utils/imgui_widgets/DefaultDebugWidget.h"

namespace prx {

	class Scene;
	class ImGuiWidget;

	enum class SceneState {
		PLAY, STOP
	};

	enum class RendererType {
		FORWARD_RENDERER,
		DEFFERED_RENDERER
	};

	class Director final : public Singleton<Director> {
		PRX_DISALLOW_COPY_AND_MOVE(Director)
	public:
		friend class Singleton<Director>;

	private:
		inline static const int MIN_DEPTH_VALUE = -10;
		inline static const int MAX_DEPTH_VALUE = 10;

	private:
		std::map<unsigned, Scene*> m_Scenes;
		std::map<std::string, unsigned> m_ScenesList;

		RendererType m_RendererType;
		Renderer2D* m_Renderer;

#ifdef PARALLAX_USING_IMGUI
		DefaultDebugWidget* m_DebugLayer;
		std::vector<ImGuiWidget*> m_DebugMenuItems;
#endif

		Scene*		m_CurrentScene;
		SceneState	m_SceneState;

		hpm::vec2	m_CurrentCameraPosition;
		hpm::vec2	m_CurrentCameraViewSpaceSize;

		hpm::vec2	m_ViewportSize;

#ifdef PARALLAX_USING_IMGUI
		bool m_DebugLayerEnabled;
#endif

		Director(RendererType renderer);
	public:
		static int minDepthValue() noexcept;
		static int maxDepthValue() noexcept;

		~Director();

		void update();
		void render();

		// TODO: Make it memory safe (smart pointers?)
		void addDebugMenuItem(ImGuiWidget* widget);
		void clearDebugMenu();

		void enableDebugLayer(bool enabled);

		unsigned int createScene(std::string_view name);
		Scene* getScene(std::string_view name);
		Scene* getScene(unsigned ID);

		const hpm::vec2& getViewport() const;

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

	private:
#ifdef PARALLAX_USING_IMGUI
		void showDebugLayer();
#endif
	};
}
