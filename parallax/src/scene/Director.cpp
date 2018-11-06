#include "Director.h"
#include "../utils/log/Log.h"
#include "../window/Window.h"
#include "../utils/error_handling/GLErrorHandler.h"
#include "../scene/Scene.h"
#include "../renderer/ForwardRenderer2D.h"
#include "../camera/Camera2D.h"
#ifdef PARALLAX_USING_IMGUI
#include "../utils/imgui_widgets/DefaultDebugWidget.h"
#include "../ext/imgui/imgui.h"
#include "../ext/imgui/imgui_impl_opengl3.h"
#include "../ext/imgui/imgui_impl_glfw.h"
#endif

namespace prx {

	int Director::minDepthValue() noexcept {
		return MIN_DEPTH_VALUE;
	}

	int Director::maxDepthValue() noexcept {
		return MAX_DEPTH_VALUE;
	}

	Director::Director()
		: Singleton<prx::Director>()
		, m_CurrentScene(nullptr)
		, m_SceneState(SceneState::STOP)
		, m_CurrentCameraPosition(0.0f)
		, m_CurrentCameraViewSpaceSize(0.0f)
		, m_ViewportSize(0.0f)
#ifdef PARALLAX_USING_IMGUI
		, m_DebugLayerEnabled(false)
#endif
	{
#ifdef PARALLAX_USING_IMGUI
		m_DebugWidgets.push_back(new DefaultDebugWidget());
#endif
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_ViewportSize = Window::getCurrentWindow().getSize();
		m_Renderer = new ForwardRenderer2D(hpm::mat4::ortho(0, m_ViewportSize.x, m_ViewportSize.y, 0,
											static_cast<float>(minDepthValue()), static_cast<float>(maxDepthValue())));
		m_Renderer->init();
	}

	Director::~Director() {
		m_Renderer->destroy();
		delete m_Renderer;

		for (auto scene : m_Scenes)
			delete scene.second;

#ifdef PARALLAX_USING_IMGUI
		delete m_DebugWidgets[DEFAULT_DEBUG_WIDGET_LOCATION];
#endif
	}

	void Director::update() {
		if (m_SceneState == SceneState::PLAY)
		m_CurrentScene->update();
		// TODO: Update only when projection matrix changed
		m_Renderer->setProjectionMatrix(m_CurrentScene->getCamera().getProjectionMatrix());
	}

	void Director::render() {
		if (m_SceneState == SceneState::PLAY)
			m_CurrentScene->draw();

#ifdef PARALLAX_USING_IMGUI
		if (m_DebugLayerEnabled) {
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			for (auto widget : m_DebugWidgets)
				widget->show();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}
#endif
	}

	void Director::addDebugWidget(ImGuiWidget* widget) {
#ifdef PARALLAX_USING_IMGUI
		m_DebugWidgets.push_back(widget);
#endif
	}

	void Director::enableDebugLayer(bool enabled) {
#ifdef PARALLAX_USING_IMGUI
		m_DebugLayerEnabled = enabled;
#endif
	}

	unsigned Director::createScene(std::string_view name) {
		Scene* scene = new Scene(name, m_Renderer);
		m_Scenes[scene->getID()] = scene;
		m_ScenesList[std::string(name)] = scene->getID();
		return scene->getID();
	}

	Scene* Director::getScene(std::string_view name) {
		auto result = m_Scenes.find(m_ScenesList.find(std::string(name))->second);
		return result->second;
	}

	Scene* Director::getScene(unsigned ID) {
		auto result = m_Scenes.find(ID);
		return result->second;
	}

	void Director::setCurrentScene(std::string_view name) {
		if (m_CurrentScene != nullptr)
			m_CurrentScene->destroy();
		m_CurrentScene = getScene(name);
		m_CurrentScene->init();
		m_CurrentScene->setRenderer(m_Renderer);
		m_SceneState = SceneState::STOP;
		// TODO: GC policies
		ResourceManager::getInstance()->collectGarbage();
	}

	void Director::setCurrentScene(unsigned ID) {
		if (m_CurrentScene != nullptr)
			m_CurrentScene->destroy();
		m_CurrentScene = getScene(ID);
		m_CurrentScene->init();
		m_CurrentScene->setRenderer(m_Renderer);
		m_SceneState = SceneState::STOP;
		// TODO: GC policies
		ResourceManager::getInstance()->collectGarbage();
	}

	void Director::initScene() {
		m_CurrentScene->init();
	}

	void Director::destroyScene() {
		m_CurrentScene->destroy();
	}

	void Director::deleteScene(std::string_view name) {
		auto node = m_Scenes.find(m_ScenesList.find(std::string(name))->second);
		if (node->second == m_CurrentScene) {
			PRX_ERROR("DIRECTOR: Can not delete current scene./n-> SCENE: ", m_CurrentScene->getName());
			return;
		}
		delete node->second;
		m_Scenes.erase(node);
		m_ScenesList.erase(std::string(name));
	}

	void Director::deleteScene(unsigned ID) {
		auto node = m_Scenes.find(ID);
		if (node->second == m_CurrentScene) {
			PRX_ERROR("DIRECTOR: Can not delete current scene./n-> SCENE: ", m_CurrentScene->getName());
			return;
		}
		delete node->second;
		m_Scenes.erase(node);
		for (auto iter : m_ScenesList) {
			if (iter.second == ID)
				m_ScenesList.erase(iter.first);
			break;
		}
	}

	void Director::playScene() noexcept {
		if (m_CurrentScene->isInitialized())
			m_SceneState = SceneState::PLAY;
		else
			PRX_ERROR("DIRECTOR: Can not play scene. Scene is not initialized/n->SCENE: ", m_CurrentScene->getName());
	}

	void Director::stopScene() noexcept {
		m_SceneState = SceneState::STOP;
	}

	void Director::setViewport(hpm::vec2 size) {
		m_ViewportSize = size;
		GLCall(glViewport(0, 0, static_cast<unsigned>(size.x), static_cast<unsigned>(size.y)));
		// TODO: Maybe not setting camera projection matrix when resizing window and make matrix independent. It should be setting by user
		//updateViewport();
	}

	void Director::updateViewport() {
		for (auto iterator : m_Scenes)
			iterator.second->setCameraViewSpaceSize(m_ViewportSize);
	}
}
