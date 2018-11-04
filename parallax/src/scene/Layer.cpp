#include "Layer.h"
#include "Scene.h"
#include "Director.h"

namespace prx {
	Layer::Layer(Scene* scene, int depth)
		: Node(scene, nullptr),
		  m_ParentScene(scene) 
	{
		m_InViewSpace = true;
		m_VisibilityTestEnabled = false;
		if (scene != nullptr)
			scene->addChild(this);
		m_Depth = depth;
	}

	void Layer::update() {
		if (m_Initialized) {
			if (!m_Frozen) {

				updateInternal();

				if (m_DepthUpdate) {
					if (m_ParentScene != nullptr)
						m_ParentScene->sortRequest();
					for (auto child : m_Children) {
						child->depthUpdateQuery();
						child->update();
					}
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
