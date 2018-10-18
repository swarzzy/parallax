#pragma once
#include <vector>
#include <hypermath.h>

namespace prx {
	
	class Renderer2D;

	class Node {
/* NOTE:
 *	Another way to make anchor points is set some size to every node, 
 *	multiply a world matrix by an anchor matix, 
 *	and the multiply by inverse anchor mat 
 *	when passing renderable to renderer. With the method it uses now
 *	anchor point only applied to a renderable nodes
 */
	protected:
		inline static unsigned int	globalNodeCounter = 0;
		
		inline static int			defaultNodeDepth = 0;
		inline static hpm::vec2		defaultAnchorPoint = hpm::vec2(0.0f);

	protected:	
		unsigned int		m_ID;
		Node*				m_Parent;
		std::vector<Node*>	m_Children;

		hpm::mat3			m_LocalMat;
		hpm::mat3			m_WorldMat;
		hpm::mat3			m_AnchorMat;
		int					m_Depth;
		bool				m_NeedsUpdate;

		hpm::vec2			m_Position;
		float				m_Scale;
		float				m_RotationAngle;
		float				m_RotationRadius;
		hpm::vec2			m_Size;
		hpm::vec2			m_AnchorPoint;

		// Internal flags. Used in updatePosition method
		bool				m_NeedsLocalMatUpdate;
		bool				m_NeedsAnchorMatUpdate;
	
		inline Node(Node* parent = nullptr, float width = 0, float height = 0);
	 
	public:
		virtual ~Node() = default;

		/*
		* These methods must call appropriate methods 
		* for children after all actions have been completed.
		*/
		virtual void init() {};
		virtual void update() = 0;
		virtual void draw(Renderer2D* renderer) {}
	
		
		virtual inline void setParent(Node* parent);
	
		inline constexpr unsigned int getID() const noexcept;
		inline Node* getParent() const noexcept;
		inline const hpm::mat3& getTransformMat() const noexcept;
		inline const hpm::mat3& getWorldMat() const noexcept;
		inline int getDepth() const noexcept;
	
		/*inline void setTransform(const hpm::mat3& transform) noexcept;*/
		inline void setPosition(const hpm::vec2& position) noexcept;
		inline void setPosition(float x, float y) noexcept;
		inline void setScale(float scale) noexcept;
		inline void setRotation(float angle) noexcept;
		inline void setRotation(float angle, float radius) noexcept;
		inline void setAnchorPoint(hpm::vec2 anchorPoint) noexcept;
		inline void setAnchorPoint(float x, float y) noexcept;

		inline void makeNeedsUpdate();
		
	protected:
		inline void addChild(Node* child);

		// These methods must be called in init, draw and update overridden methods
		inline void initChildren();

		inline void updatePosition();
		inline void updateChildren();
		// This method used when parent node was updated to recalculate all children positions
		inline void forceUpdateChildren();

		inline void drawChildren(Renderer2D* renderer);

	public:
		Node(const Node& other) = delete;
		Node(const Node&& other) = delete;
		Node(Node&& other) = delete;
		Node& operator=(const Node& other) = delete;
		Node& operator=(const Node&& other) = delete;
		Node& operator=(Node&& other) = delete;
	 };
 }
#include "Node.inl"
