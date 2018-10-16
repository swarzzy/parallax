#include <scene/Scene.h>
#include <window/Window.h>
#include <renderer/Renderer2D.h>
#include <camera/Camera2D.h>

namespace prx {
	Scene::Scene(Renderer2D* renderer, Node* parent) 
		: Node(parent),
		  m_Renderer(renderer),
		  m_Camera(new Camera2D()),
		  m_CameraMoved(false)
	{
		auto winWidth = Window::getCurrentWindow().getWidth();
		auto winHeight = Window::getCurrentWindow().getHeight();
		
		m_LocalMat = hpm::mat3::translation(winWidth / 2.0f, winHeight / 2.0f);
	}

	Scene::~Scene() {
		for (auto child : m_Children) {
			delete child;
		}
	}

	void Scene::init() {
		auto width = Window::getCurrentWindow().getWidth();
		auto height = Window::getCurrentWindow().getHeight();
		m_Camera->init(hpm::vec2(width / 2, height / 2), -10, 10, width, height);
		m_Renderer->setProjectionMatrix(m_Camera->getProjectionMatrix());
	}

	void Scene::update() {
		m_Camera->update();
		if (m_NeedsUpdate) {
			updatePosition();
			forceUpdateChildren();
		}
		else
			updateChildren();
	}

	void Scene::draw(Renderer2D* renderer) {
		//
	}

	void Scene::present() {
		if (m_CameraMoved) {
			m_Renderer->setProjectionMatrix(m_Camera->getProjectionMatrix());
			m_CameraMoved = false;
		}
		m_Renderer->begin();
		drawChildren(m_Renderer);
		m_Renderer->end();
		m_Renderer->flush();
	}

	void Scene::setCameraPosition(hpm::vec2 position) noexcept {
		m_Camera->setCameraPosition(position);
		m_CameraMoved = true;
	}

	void Scene::setCameraPosition(float x, float y) noexcept {
		m_Camera->setCameraPosition(x, y);
		m_CameraMoved = true;
	}


}

