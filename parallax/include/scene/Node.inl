#include "../utils/log/Log.h"

namespace prx {
	
	Node::Node(Node* parent, float width, float height)
		: m_ID(++globalNodeCounter),
		  m_Parent(parent),
		  m_LocalMat(hpm::mat4::identity()),
		  m_WorldMat(hpm::mat4::identity()),
		  m_AnchorMat(hpm::mat3::identity()),
		  m_Depth(0),
		  m_NeedsUpdate(true),
		  m_Position(hpm::vec2(0.0f)),
		  m_Scale(1.0f),
		  m_RotationAngle(0.0f),
		  m_RotationRadius(0.0f),
		  m_Size(width, height),
		  m_AnchorPoint(defaultAnchorPoint),
		  m_NeedsLocalMatUpdate(true),
		  m_NeedsAnchorMatUpdate(true)
	{
		if (parent != nullptr) {
			parent->addChild(this);
			m_Depth = parent->m_Depth;
		} else {
			m_Depth = defaultNodeDepth;
		}
	}

	inline void Node::addChild(Node* child) {
		m_Children.push_back(child);
	}

	inline void Node::setParent(Node* parent) {
		if (parent == this)
			PRX_ERROR("(Node): Trying to set self as a parent\n-> Node ID: ", m_ID);
		m_Parent = parent;
		parent->addChild(this);
		m_Depth = parent->m_Depth;
	}

	inline void Node::makeNeedsUpdate() {
		m_NeedsUpdate = true;
	}

	inline constexpr unsigned int Node::getID() const noexcept {
		return m_ID;
	}

	inline Node* Node::getParent() const noexcept {
		return m_Parent;
	}

	inline const hpm::mat3& Node::getTransformMat() const noexcept {
		return m_LocalMat;
	}

	inline const hpm::mat3& Node::getWorldMat() const noexcept {
		return m_WorldMat;
	}

	/*inline void Node::setTransform(const hpm::mat3& transform) noexcept {
		m_LocalMat = transform;
		m_NeedsUpdate = true;
	}*/

	inline void Node::setPosition(const hpm::vec2& position) noexcept {
		m_Position = position;
		m_NeedsUpdate = true;
		m_NeedsLocalMatUpdate = true;
	}

	inline void Node::setPosition(float x, float y) noexcept {
		m_Position = hpm::vec2(x, y);
		m_NeedsUpdate = true;
		m_NeedsLocalMatUpdate = true;
	}

	inline void Node::setScale(float scale) noexcept {
		m_Scale = scale;
		m_NeedsUpdate = true;
		m_NeedsLocalMatUpdate = true;
	}

	inline void Node::setRotation(float angle) noexcept {
		m_RotationAngle = angle;
		m_RotationRadius = 0.0f;
		m_NeedsUpdate = true;
		m_NeedsLocalMatUpdate = true;
	}

	inline void Node::setRotation(float angle, float radius) noexcept {
		m_RotationAngle = angle;
		m_RotationRadius = radius;
		m_NeedsUpdate = true;
		m_NeedsLocalMatUpdate = true;
	}

	inline void Node::setAnchorPoint(hpm::vec2 anchorPoint) noexcept {
		m_AnchorPoint = anchorPoint;
		m_NeedsUpdate = true;
		m_NeedsLocalMatUpdate = true;
	}

	inline void Node::setAnchorPoint(float x, float y) noexcept {
		m_AnchorPoint = hpm::vec2(x ,y);
		m_NeedsUpdate = true;
		m_NeedsLocalMatUpdate = true;
		m_NeedsAnchorMatUpdate = true;
	}

	inline void Node::initChildren() {
		for (auto child : m_Children) {
			child->init();
			child->initChildren();
		}
	}

	inline void Node::updatePosition() {
		if (m_NeedsAnchorMatUpdate) {
			m_AnchorMat = hpm::mat3::translation(-(m_Size.x * m_AnchorPoint.x), -(m_Size.y * m_AnchorPoint.y));
			m_NeedsAnchorMatUpdate = false;
		}
		if (m_NeedsLocalMatUpdate) {
			m_LocalMat = hpm::mat3::translation(m_Position)
				* hpm::mat3::rotation(m_RotationAngle)
				* hpm::mat3::translation(m_RotationRadius, m_RotationRadius)
				* hpm::mat3::scale(hpm::vec2(m_Scale));
			m_NeedsLocalMatUpdate = false;
		}
		if (m_Parent != nullptr) {
			m_WorldMat = m_Parent->getWorldMat() * m_LocalMat;
			m_Depth = m_Parent->m_Depth;
		}
		else {
			m_WorldMat = m_WorldMat * m_LocalMat;
		}
		m_NeedsUpdate = false;
	}

	inline void Node::updateChildren() {
		for (auto child : m_Children) {
			child->update();
			child->updateChildren();
		}
	}

	inline void Node::forceUpdateChildren() {
		for (auto child : m_Children) {
			child->makeNeedsUpdate();
			child->update();
			child->updateChildren();
		}
	}

	inline void Node::drawChildren(Renderer2D* renderer) {
		for (auto child : m_Children) {
			child->draw(renderer);
		}
		
	}
	inline int Node::getDepth() const noexcept {
		return m_Depth;
	}
}
