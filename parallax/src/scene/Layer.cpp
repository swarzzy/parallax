#include <scene/Layer.h>
#include <scene/Scene.h>

namespace prx {
	int Layer::minDepthValue() noexcept {
		return MIN_DEPTH_VALUE;
	}

	int Layer::maxDepthValue() noexcept {
		return MAX_DEPTH_VALUE;
	}

	Layer::Layer(int depth, Node* parent)
		: Node(parent)
	{
		if (parent == nullptr)
			m_ParentScene = nullptr;
		else {
			m_Parent = parent;
			if (Scene* scene = dynamic_cast<Scene*>(parent)) {
				m_ParentScene = scene;
				m_Depth = depth;
			} else {
				m_Depth = m_Parent->getDepth();
			}
		}
	}

	void Layer::update() {
#ifdef PARALLAX_DEBUG
		if (!m_Initialized)
			PRX_FATAL("NODE: Node is not initialized (Node ID: ", m_ID, " )");
#endif
		if (m_DepthUpdate) {
			if (m_ParentScene != nullptr) 
				m_ParentScene->sortRequest();
			else if (m_Parent != nullptr)
				m_Depth = m_Parent->getDepth();
		PRX_INFO("depth uppdate ", m_ID);
		}

		if (m_TransformUpdate) {
			if (m_Parent != nullptr)
				m_TransformComponent.setWorldMat(m_Parent->getWorldMat());
			m_TransformComponent.update();
			PRX_INFO("transform uppdate ", m_ID);
		}

		updateInternal();

		if (m_DepthUpdate && m_TransformUpdate)
			for (auto child : m_Children) {
				child->depthUpdateQuery();
				child->transformUpdateQuery();
				child->update();
			}
		else if (m_DepthUpdate)
			for (auto child : m_Children) {
				child->depthUpdateQuery();
				child->update();
			}
		else if (m_TransformUpdate)
			for (auto child : m_Children) {
				child->transformUpdateQuery();
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

	void Layer::setDepth(int depth) {
		if (m_ParentScene != nullptr) {
			if (depth >= MIN_DEPTH_VALUE && depth <= MAX_DEPTH_VALUE) {
				m_Depth = depth;
				m_DepthUpdate = true;
			}
			else {
				PRX_WARN("(Layer): Incorrect depth value. Value sould be between: ",
					MIN_DEPTH_VALUE, " and ", MAX_DEPTH_VALUE, ".");
			}
		}
	}
}
