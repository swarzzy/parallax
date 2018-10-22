#include <scene/Layer.h>
#include <scene/Scene.h>
#include <scene/Director.h>

namespace prx {
	Layer::Layer(int depth, Scene* parent)
		: Node(nullptr),
		  m_ParentScene(parent) 
	{
		m_InViewSpace = true;
		m_VisibilityTestEnabled = false;
		if (parent != nullptr)
			parent->addChild(this);
	}

	void Layer::update() {
#ifdef PARALLAX_DEBUG
		if (!m_Initialized)
			PRX_FATAL("LAYER: Layer is not initialized (Node ID: ", m_ID, " )");
#endif
		if (!m_Frozen) {

			if (m_DepthUpdate) {
				if (m_ParentScene != nullptr)
					m_ParentScene->sortRequest();
				else if (m_Parent != nullptr)
					m_Depth = m_Parent->getDepth();
				PRX_INFO("depth update ", m_ID);
			}

			updateInternal();

			if (m_DepthUpdate)
				for (auto child : m_Children) {
					child->depthUpdateQuery();
					child->update();
				}
			else {
				for (auto child : m_Children) {
					child->update();
				}
			}

			m_DepthUpdate = false;
			m_TransformUpdate = false;
		}
	}

	void Layer::setParent(Scene* parent) {
		m_ParentScene->removeChild(this);
		m_ParentScene = parent;
		parent->addChild(this);
	}

	void Layer::setDepth(int depth) {
		if (m_ParentScene != nullptr) {
			if (depth >= Director::minDepthValue() && depth <= Director::maxDepthValue()) {
				m_Depth = depth;
				m_DepthUpdate = true;
			}
			else {
				PRX_WARN("LAYER: Incorrect depth value. Value sould be between: ",
					Director::minDepthValue(), " and ", Director::maxDepthValue(), ".");
			}
		}
	}
}
