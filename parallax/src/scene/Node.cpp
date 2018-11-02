#include "Node.h"
#include "Scene.h"

namespace prx {
	void Node::visibilityTestAnchor() {
		const hpm::vec2& cameraPosition = Scene::getCurrentCameraPosition();
		const hpm::vec2& cameraViewSize = Scene::getCurrentCameraViewSize();
		hpm::vec2 nodePosition = m_TransformComponent.getWorldMat() * hpm::vec2(0.0f);
		hpm::vec2 projection = nodePosition - cameraPosition;

		m_InViewSpace = (projection.x >= 0.0f && projection.y >= 0.0f)
					 && (projection.x < cameraViewSize.x && projection.y < cameraViewSize.y);
	}

	void Node::visibilityTestQuad() {
		const hpm::vec2& cameraPosition = Scene::getCurrentCameraPosition();
		const hpm::vec2& cameraViewSize = Scene::getCurrentCameraViewSize();
		hpm::vec2 nodePosition = m_TransformComponent.getWorldMat() * hpm::vec2(0.0f);
		hpm::vec2 projection = nodePosition - cameraPosition;

		bool testRightUpEdge = projection.x < cameraViewSize.x && projection.y < cameraViewSize.y;

		nodePosition = hpm::vec2(nodePosition.x + m_TransformComponent.getSize().x * m_TransformComponent.getScale(),
			nodePosition.y + m_TransformComponent.getSize().y * m_TransformComponent.getScale());
		projection = nodePosition - cameraPosition;

		bool testLeftDownEdge = projection.x > 0.0f && projection.y > 0.0f;

		m_InViewSpace = testRightUpEdge && testLeftDownEdge;
	}
	
	Renderer2D * Node::getRenderer() const noexcept {
		return m_Scene->m_Renderer;
	}
}