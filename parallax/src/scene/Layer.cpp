#include <scene/Layer.h>
#include <scene/Scene.h>

namespace prx {
	Layer::Layer(int depth, Node* parent)
		: Node(parent),
		  m_DepthUpdated(false)
	{  
		m_Depth = depth;

		if (parent == nullptr)
			m_ParentScene = nullptr;
		else {
			m_Parent = parent;
			if (Scene* scene = dynamic_cast<Scene*>(parent))
				m_ParentScene = scene;
		}
	}

	void Layer::init() {
		if (m_ParentScene != nullptr)
			m_ParentScene->sortRequest();
		initChildren();
	}

	void Layer::update() {
		if (m_NeedsUpdate) {
			updatePosition();
			forceUpdateChildren();
		}
		else
			updateChildren();
		
		if (m_DepthUpdated && m_ParentScene != nullptr) {
			m_ParentScene->sortRequest();
			m_DepthUpdated = false;
		}
	}

	void Layer::draw(Renderer2D* renderer) {
		drawChildren(renderer);
	}

	void Layer::setDepth(int depth) {
		if (depth >= minDepthValue && depth <= maxDepthValue) {
			m_Depth = depth;
			m_DepthUpdated = true;
		} else {
			PRX_WARN("(Layer): Incorrect depth value. Value sould be between: ", 
					 minDepthValue, " and ", maxDepthValue, ".");
		}
	}
}
