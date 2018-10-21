#include "../utils/log/Log.h"
#include "Node.h"

namespace prx {
	inline int Node::defaultNodeDepth() noexcept{
		return DEFAULT_NODE_DEPTH;
	}

	inline const hpm::vec2 Node::defaultAnchorPoint() noexcept {
		return DEFAULT_ANCHOR_POINT;
	}

	Node::Node(Node* parent, float width, float height)
		: m_ID(++GLOBAL_NODE_COUNTER),
		  m_Parent(parent),
		  m_Initialized(false),
		  m_TransformUpdate(true),
		  m_Frozen(false),
		  m_Visible(true),
		  m_Depth(DEFAULT_NODE_DEPTH),
		  m_DepthUpdate(true),
		  m_InViewSpace(false),
		  m_VisibilityTestEnabled(true),
		  m_VisibilityTestMode(DEFAULT_VISIBILITY_TEST_MODE)
	{
		if (parent != nullptr) {
			parent->addChild(this);
			m_Depth = parent->m_Depth;
		}
	}

	Node::~Node() {
		for (auto child : m_Children) {
			delete child;
		}
	}

	inline void Node::init() {
		if (!m_Initialized) {
		m_Initialized = true;

		if (m_Parent != nullptr) {
			m_Depth = m_Parent->m_Depth;
			m_TransformComponent.setWorldMat(m_Parent->getWorldMat());
		}

		m_TransformComponent.init();
		
		initInternal();

		for (auto child : m_Children)
			child->init();
		}

		m_DepthUpdate = false;
		m_TransformUpdate = false;

		if (m_VisibilityTestEnabled) {
			m_InViewSpace = false;
			if (m_VisibilityTestMode == VisibilityTestMode::QUAD)
				visibilityTestQuad();
			else
				visibilityTestAnchor();
		}
		else
			m_InViewSpace = true;
	}

	inline void Node::update() {
#ifdef PARALLAX_DEBUG
		if (!m_Initialized)
			PRX_FATAL("NODE: Node is not initialized (Node ID: ", m_ID, " )");
#endif
		if (!m_Frozen) {

			if (m_DepthUpdate) {
				if (m_Parent != nullptr)
					m_Depth = m_Parent->m_Depth;
				//PRX_INFO("depth uppdate ", m_ID);
			}

			if (m_TransformUpdate) {
				if (m_Parent != nullptr)
					m_TransformComponent.setWorldMat(m_Parent->getWorldMat());
				m_TransformComponent.update();
				//PRX_INFO("transform uppdate ", m_ID);
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

			if (m_Visible) {
				if (m_VisibilityTestEnabled) {
					m_InViewSpace = false;
					if (m_VisibilityTestMode == VisibilityTestMode::QUAD)
						visibilityTestQuad();
					else
						visibilityTestAnchor();
				}
				else
					m_InViewSpace = true;
			}
		}
	}

	inline void Node::draw(Renderer2D * renderer) {
#ifdef PARALLAX_DEBUG
		if (!m_Initialized)
			PRX_FATAL("(Node): Node is not initialized (Node ID: )", m_ID);
#endif
		if (m_Visible && m_InViewSpace) {
			drawInternal(renderer);

			for (auto child : m_Children)
				child->draw(renderer);
		}
	}

	inline void Node::addChild(Node* child) {
		m_Children.push_back(child);
	}

	inline void Node::setParent(Node* parent) {
		if (parent == this)
			PRX_ERROR("(Node): Trying to set self as a parent\n-> Node ID: ", m_ID);
		m_Parent->removeChild(this);
		m_Parent = parent;
		parent->addChild(this);
		m_Depth = parent->m_Depth;
	}

	inline void Node::removeChild(Node * child){
		auto result = std::find(m_Children.begin(), m_Children.end(), child);
		m_Children.erase(result);
	}

	inline bool Node::isInitialized() const noexcept {
		return m_Initialized;
	}

	inline constexpr unsigned int Node::getID() const noexcept {
		return m_ID;
	}

	inline Node* Node::getParent() const noexcept {
		return m_Parent;
	}

	inline const hpm::mat3& Node::getLocalMat() const noexcept {
		return m_TransformComponent.getLocalMat();
	}

	inline const hpm::mat3& Node::getWorldMat() const noexcept {
		return m_TransformComponent.getWorldMat();
	}

	inline void Node::setPosition(const hpm::vec2& position) noexcept {
		m_TransformComponent.setPosition(position);
		m_TransformUpdate = true;
	}

	inline void Node::setPosition(float x, float y) noexcept {
		m_TransformComponent.setPosition(x, y);
		m_TransformUpdate = true;
	}

	inline void Node::setScale(float scale) noexcept {
		m_TransformComponent.setScale(scale);
		m_TransformUpdate = true;
	}

	inline void Node::setRotation(float angle, float radius) noexcept {
		m_TransformComponent.setRotation(angle, radius);
		m_TransformUpdate = true;
	}

	inline void Node::setAnchorPoint(hpm::vec2 anchorPoint) noexcept {
		m_TransformComponent.setAnchorPoint(anchorPoint);
		m_TransformUpdate = true;
	}

	inline void Node::setAnchorPoint(float x, float y) noexcept {
		m_TransformComponent.setAnchorPoint(x, y);
		m_TransformUpdate = true;
	}

	inline void Node::hide(bool hide) noexcept {
		m_Visible = !hide;
	}

	inline bool Node::isHidden() const noexcept {
		return !m_Visible;
	}

	inline void Node::enableVisibilityTest(bool enable) noexcept {
		m_VisibilityTestEnabled = enable;
	}

	inline void Node::setVisibilityTestMode(VisibilityTestMode mode) noexcept {
		m_VisibilityTestMode = mode;
	}

	inline bool Node::isCulled() const noexcept {
		return !m_InViewSpace;
	}

	inline void Node::freeze(bool freeze) noexcept {
		m_Frozen = freeze;
	}

	inline bool Node::isFrozen() const noexcept {
		return m_Frozen;
	}

	inline void Node::depthUpdateQuery() noexcept {
		m_DepthUpdate = true;
	}

	inline void Node::transformUpdateQuery() noexcept {
		m_TransformUpdate = true;
	}

	inline int Node::getDepth() const noexcept {
		return m_Depth;
	}
}