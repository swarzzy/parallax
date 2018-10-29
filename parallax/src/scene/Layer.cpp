#include <scene/Layer.h>
#include <scene/Scene.h>
#include <scene/Director.h>

namespace prx {
	Layer::Layer(Scene* scene, int depth)
		: Node(scene, nullptr),
		  m_ParentScene(scene) 
	{
		m_InViewSpace = true;
		m_VisibilityTestEnabled = false;
		if (scene != nullptr)
			scene->addChild(this);
	}

	void Layer::update() {
		if (m_Initialized) {
			if (!m_Frozen) {

				if (m_DepthUpdate) {
					if (m_ParentScene != nullptr)
						m_ParentScene->sortRequest();
					// TODO: remove this
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
