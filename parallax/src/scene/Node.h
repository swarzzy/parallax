#pragma once
#include <vector>
#include <hypermath.h>
#include "../Common.h"
#include "../scene/components/TransformComponent2D.h"

namespace prx {
	
	class Renderer2D;
	class Scene;

	enum class VisibilityTestMode {
		ANCHOR_POINT,
		QUAD
	};

	class Node {
		PRX_DISALLOW_COPY_AND_MOVE(Node)
/* NOTE:
 *	Another way to make anchor points is set some size to every node, 
 *	multiply a world matrix by an anchor matix, 
 *	and the multiply by inverse anchor mat 
 *	when passing renderable to renderer. With the method it uses now
 *	anchor point only applied to a renderable nodes
 */
	protected:
		inline static unsigned int		 GLOBAL_NODE_COUNTER		  = 0;
		inline static const int			 DEFAULT_NODE_DEPTH			  = 0;
		inline static const hpm::vec2	 DEFAULT_ANCHOR_POINT		  = hpm::vec2(0.0f);
		inline static VisibilityTestMode DEFAULT_VISIBILITY_TEST_MODE = VisibilityTestMode::QUAD;

	public:
		static inline int defaultNodeDepth() noexcept;
		static inline const hpm::vec2 defaultAnchorPoint() noexcept;

		friend class Scene;

	protected:

		unsigned int		 m_ID;
		Scene*				 m_Scene;
		Node*				 m_Parent;
		std::vector<Node*>	 m_Children;
		bool				 m_Initialized;
		
		TransformComponent2D m_TransformComponent;
		bool				 m_TransformUpdate;
		bool				 m_Frozen;
		
		bool				 m_Visible;
		int					 m_Depth;
		bool				 m_DepthUpdate;
		bool				 m_InViewSpace;
		bool				 m_VisibilityTestEnabled;
		VisibilityTestMode	 m_VisibilityTestMode;
	
		inline Node(Scene* scene, Node* parent = nullptr, float width = 0, float height = 0);
	 
	public:
		inline virtual ~Node();

		inline void init();
		virtual inline void update();
		inline void draw();
		inline void destroy();
	
		virtual inline void setParent(Node* parent);
		inline void removeChild(Node* child);
		inline Node* getParent() const noexcept;
		inline const std::vector<Node*>& getChildren() const noexcept;

		inline bool isInitialized() const noexcept;
	
		inline int getDepth() const noexcept;
		inline constexpr unsigned int getID() const noexcept;
		inline const Scene* getScene() const noexcept;
		inline const hpm::mat3& getLocalMat() const noexcept;
		inline const hpm::mat3& getWorldMat() const noexcept;
		
		Renderer2D* getRenderer() const noexcept;
	
		virtual inline void setPosition(const hpm::vec2& position) noexcept;
		virtual inline void setPosition(float x, float y) noexcept;
		virtual inline void setScale(float scale) noexcept;
		virtual inline void setSize(float width, float height) noexcept;
		virtual inline void setSize(const hpm::vec2& size) noexcept;
		virtual inline void setRotation(float angle, float radius = 0) noexcept;
		virtual inline void setAnchorPoint(hpm::vec2 anchorPoint) noexcept;
		virtual inline void setAnchorPoint(float x, float y) noexcept;

		virtual inline void hide(bool hide) noexcept;
		inline bool isHidden() const noexcept;

		virtual inline void enableVisibilityTest(bool enable) noexcept;
		virtual inline void setVisibilityTestMode(VisibilityTestMode mode) noexcept;
		inline bool isCulled() const noexcept;

		virtual inline void freeze(bool freeze) noexcept;
		inline bool isFrozen() const noexcept;

		inline void depthUpdateQuery() noexcept;
		inline void transformUpdateQuery() noexcept;
		
	protected:
		// These methods will contain the user code in derived classes
		virtual void initInternal() {};
		virtual void updateInternal() {};
		virtual void drawInternal() {};
		virtual void destroyInternal() {};

		inline void addChild(Node* child);

		void visibilityTestAnchor();
		void visibilityTestQuad();
	 };
 }
#include "Node.inl"
