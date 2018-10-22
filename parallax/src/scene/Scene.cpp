#include <scene/Scene.h>
#include <window/Window.h>
#include <renderer/Renderer2D.h>
#include <camera/Camera2D.h>
#include <scene/Layer.h>

namespace prx {

	const std::function<bool(Layer*, Layer*)> Scene::SORT_PREDICATE =
		[](Layer* a, Layer* b) {return a->getDepth() < b->getDepth(); };

	Scene::Scene(std::string_view name, Renderer2D* renderer)
		: m_ID(++GLOBAL_SCENE_COUNTER),
		m_Name(name),
		m_Renderer(renderer),
		m_Camera(new Camera2D()),
		m_CameraMoved(false),
		m_NeedsSorting(false)
	{
		m_Camera->setCameraPosition(DEFAULT_CAMERA_POSITION);
	}

	Scene::~Scene() {
		for (auto layer : m_Layers) {
			delete layer;
		}
		delete m_Camera;
		delete m_Renderer;
	}

	void Scene::sortChildren() {
		std::sort(m_Layers.begin(), m_Layers.end(), SORT_PREDICATE);
	}

	void Scene::init() {
		auto winWidth = Window::getCurrentWindow().getWidth();
		auto winHeight = Window::getCurrentWindow().getHeight();

		m_Camera->init(winWidth, winHeight);

		m_Renderer->init();
		m_Renderer->setProjectionMatrix(m_Camera->getProjectionMatrix());

		for (auto layer : m_Layers)
			layer->init();

		sortChildren();
	}

	void Scene::update() {
		m_Camera->update();
		currentCameraPosition = m_Camera->getCameraPosition();
		currentViewSize = m_Camera->getViewSpaceSize();

		for (auto layer : m_Layers)
			layer->update();
	}

	void Scene::draw() {
		if (m_NeedsSorting) {
			sortChildren();
			m_NeedsSorting = false;
		}

		if (m_CameraMoved) {
			m_Renderer->setProjectionMatrix(m_Camera->getProjectionMatrix());
			m_CameraMoved = false;
		}

		m_Renderer->begin();
		for (auto layer : m_Layers)
			layer->draw(m_Renderer);
		m_Renderer->end();
		m_Renderer->flush();
	}

	void Scene::removeChild(Layer* layer) {
		auto result = std::find(m_Layers.begin(), m_Layers.end(), layer);
		m_Layers.erase(result);
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

	void Scene::setCameraViewSpaceSize(hpm::vec2 size) noexcept {
		m_Camera->setViewSpace(size);
	}

	void Scene::setCameraViewSpaceSize(float x, float y) noexcept {
		m_Camera->setViewSpace(x, y);
	}

	const hpm::vec2& Scene::getCameraPosition() const noexcept {
		return m_Camera->getCameraPosition();
	}

	const hpm::vec2& Scene::getViewSize() const noexcept {
		return m_Camera->getViewSpaceSize();
	}

	void Scene::addChild(Layer* child) {
		if (child != nullptr) {
			m_Layers.push_back(child);
			sortRequest();
		} else {
			PRX_ERROR("SCENE: Can`t add new child. Child was nullptr\n-> SCENE ID: ",
					 m_ID, "\n-> SCENE NAME: ", m_Name);
		}
	}
}

