
#include "utils/log/Log.h"

namespace prx {
	
	Node::Node(Node* parent, Renderer2D* renderer)
		: m_ID(++m_GlobalNodeCounter),
		  m_Parent(parent), 
		  m_NeedsUpdate(true),
		  m_LocalMat(hpm::mat4::identity()),
		  m_WorldMat(hpm::mat4::identity()),
		  m_Renderer(renderer)
	{
		if (parent != nullptr)
			parent->addChild(this);
	}

	inline void Node::addChild(Node* child) {
		m_Children.push_back(child);
	}

	inline void Node::setParent(Node* parent) {
		if (parent == this)
			PRX_ERROR("(Node): Trying to set self as a parent\n-> Node ID: ", m_ID);
		m_Parent = parent;
		parent->addChild(this);
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

	inline const hpm::mat4& Node::getTransformMat() const noexcept {
		return m_LocalMat;
	}

	inline const hpm::mat4& Node::getWorldMat() const noexcept {
		return m_WorldMat;
	}

	inline void Node::setTransform(const hpm::mat4& transform) noexcept {
		m_LocalMat = transform;
		m_NeedsUpdate = true;
	}

	inline void Node::updatePosition() {
		if (m_Parent != nullptr) {
			m_WorldMat = m_Parent->getWorldMat() * m_LocalMat;
			m_NeedsUpdate = false;
		}
		else {
			m_WorldMat = m_WorldMat * m_LocalMat;
			m_NeedsUpdate = false;
		}
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

	inline void Node::drawChildren() {
		for (auto child : m_Children) {
			child->draw();
			child->drawChildren();
		}
		
	}
}
