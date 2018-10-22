#include <scene/Director.h>
#include <utils/log/Log.h>
#include <window/Window.h>
#include <utils/error_handling/GLErrorHandler.h>
#include <scene/Scene.h>
#include <renderer/ForwardRenderer2D.h>

namespace prx {

	int Director::minDepthValue() noexcept {
		return MIN_DEPTH_VALUE;
	}

	int Director::maxDepthValue() noexcept {
		return MAX_DEPTH_VALUE;
	}

	Director::Director()
		: Singleton<prx::Director>(),
		  m_CurrentScene(nullptr),
		  m_SceneState(SceneState::STOP),
		  m_CurrentCameraPosition(0.0f),
		  m_CurrentCameraViewSpaceSize(0.0f),
		  m_ViewportSize(0.0f)
	{
		m_ViewportSize = Window::getCurrentWindow().getSize();
	}

	Director::~Director() {
	}

	void Director::update() {
		if (m_CurrentScene != nullptr)
			// TODO: get rid of this checking
		m_CurrentScene->update();
	}

	void Director::draw() {
		if (m_CurrentScene != nullptr)
			// TODO: get rid of this checking
			m_CurrentScene->draw();
	}

	unsigned Director::createScene(std::string_view name) {
		ForwardRenderer2D* renderer = new ForwardRenderer2D(hpm::mat4::ortho(0, m_ViewportSize.x, m_ViewportSize.y, 0,
																			 minDepthValue(), maxDepthValue()));
		Scene* scene = new Scene(name, renderer);
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
		m_CurrentScene = getScene(name);
	}

	void Director::setCurrentScene(unsigned ID) {
		m_CurrentScene = getScene(ID);
	}

	void Director::initScene() {
		m_CurrentScene->init();
	}

	void Director::setViewport(hpm::vec2 size) {
		m_ViewportSize = size;
		GLCall(glViewport(0, 0, size.x, size.y));
		updateViewport();
	}

	void Director::updateViewport() {
		for (auto iterator : m_Scenes)
			iterator.second->setCameraViewSpaceSize(m_ViewportSize);
	}
}
