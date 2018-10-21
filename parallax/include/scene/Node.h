#pragma once
#include <vector>
#include <hypermath.h>
#include "../Common.h"
#include "../scene/components/TransformComponent2D.h"

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
		inline static unsigned int		GLOBAL_NODE_COUNTER = 0;
		inline static const int			DEFAULT_NODE_DEPTH = 0;
		inline static const hpm::vec2	DEFAULT_ANCHOR_POINT = hpm::vec2(0.0f);

	public:
		static inline int defaultNodeDepth() noexcept;
		static inline const hpm::vec2 defaultAnchorPoint() noexcept;

	protected:

		PRX_DISALLOW_COPY_AND_MOVE(Node)

		unsigned int		 m_ID;
		Node*				 m_Parent;
		std::vector<Node*>	 m_Children;
		TransformComponent2D m_TransformComponent;
		int					 m_Depth;
		bool				 m_TransformUpdate;
		bool				 m_DepthUpdate;
		bool				 m_Initialized;
	
		inline Node(Node* parent = nullptr, float width = 0, float height = 0);
	 
	public:
		inline virtual ~Node();

		inline void init();
		virtual inline void update();
		inline void draw(Renderer2D* renderer);
		// TODO: Destroy method
		inline void destroy() {};
	
		virtual inline void setParent(Node* parent);
		inline void removeChild(Node* child);

		inline bool isInitialized() const noexcept;
	
		inline constexpr unsigned int getID() const noexcept;
		inline Node* getParent() const noexcept;
		inline int getDepth() const noexcept;
		inline const hpm::mat3& getLocalMat() const noexcept;
		inline const hpm::mat3& getWorldMat() const noexcept;
	
		virtual inline void setPosition(const hpm::vec2& position) noexcept;
		virtual inline void setPosition(float x, float y) noexcept;
		virtual inline void setScale(float scale) noexcept;
		virtual inline void setRotation(float angle, float radius = 0) noexcept;
		virtual inline void setAnchorPoint(hpm::vec2 anchorPoint) noexcept;
		virtual inline void setAnchorPoint(float x, float y) noexcept;

		inline void depthUpdateQuery() noexcept;
		inline void transformUpdateQuery() noexcept;
		
	protected:
		// These methods will contain the user code in derived classes
		virtual void initInternal() {};
		virtual void updateInternal() {};
		virtual void drawInternal(Renderer2D* renderer) {};

		inline void addChild(Node* child);
	 };
 }
#include "Node.inl"
