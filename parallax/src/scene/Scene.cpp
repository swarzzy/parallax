#include <scene/Scene.h>
#include <window/Window.h>
#include <renderer/Renderer2D.h>

namespace prx {
	Scene::Scene(Renderer2D* renderer, Node* parent) 
		: Node(parent),
		  m_Renderer(renderer)
	{
		auto winWidth = Window::getCurrentWindow().getWidth();
		auto winHeight = Window::getCurrentWindow().getHeight();
		float depth;
		if (parent == nullptr)
			depth = 0.0f;
		else
			depth = 0.0f;
		// TODO: get depth from the parent
		m_LocalMat = hpm::mat3::translation(winWidth / 2.0f, winHeight / 2.0f);
	}

	Scene::~Scene() {
		for (auto child : m_Children) {
			delete child;
		}
	}

	void Scene::init() {
		
	}

	void Scene::update() {
		if (m_NeedsUpdate) {
			updatePosition();
			forceUpdateChildren();
		}
		else
			updateChildren();
	}

	void Scene::draw(Renderer2D* renderer) {
		//drawChildren(renderer);
	}

	void Scene::present() {
		m_Renderer->begin();
		drawChildren(m_Renderer);
		m_Renderer->end();
		m_Renderer->flush();
	}


}

