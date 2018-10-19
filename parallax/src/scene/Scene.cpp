#include <scene/Scene.h>
#include <window/Window.h>
#include <renderer/Renderer2D.h>
#include <camera/Camera2D.h>

namespace prx {
	Scene::Scene(Renderer2D* renderer)
		: Node(nullptr),
		  m_Renderer(renderer),
		  m_Camera(new Camera2D()),
		  m_CameraMoved(false),
		  m_NeedsSorting(false) 
	{
		m_Camera->setCameraPosition(DEFAULT_CAMERA_POSITION);
	}

	Scene::~Scene() {
		for (auto child : m_Children) {
			delete child;
		}
		delete m_Camera;
	}

	void Scene::sortChildren() {
		std::sort(m_Children.begin(), m_Children.end(), SORT_PREDICATE);
	}


	void Scene::present() {
		if (m_NeedsSorting) {
			sortChildren();
			m_NeedsSorting = false;
		}

		if (m_CameraMoved) {
			m_Renderer->setProjectionMatrix(m_Camera->getProjectionMatrix());
			m_CameraMoved = false;
		}

		m_Renderer->begin();
		for (auto child : m_Children)
			child->draw(m_Renderer);
		m_Renderer->end();
		m_Renderer->flush();
	}

	void Scene::sortRequest() noexcept {
		m_NeedsSorting = true;
	}

	void Scene::setCameraPosition(hpm::vec2 position) noexcept {
		m_Camera->setCameraPosition(position);
		m_CameraMoved = true;
	}

	void Scene::setCameraPosition(float x, float y) noexcept {
		m_Camera->setCameraPosition(x, y);
		m_CameraMoved = true;
	}

	void Scene::initInternal() {
		auto winWidth = Window::getCurrentWindow().getWidth();
		auto winHeight = Window::getCurrentWindow().getHeight();

		m_Camera->init(winWidth, winHeight);

		m_Renderer->init();
		m_Renderer->setProjectionMatrix(m_Camera->getProjectionMatrix());
	}

	void Scene::updateInternal() {
		m_Camera->update();
	}
}

