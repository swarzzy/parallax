#pragma once
#include <vector>
#include <hypermath.h>

namespace prx {
	
	class Renderer2D;
	
	class Node {
	protected:
		inline static unsigned int	m_GlobalNodeCounter = 0;
	
		unsigned int		m_ID;
		Node*				m_Parent;
		std::vector<Node*>	m_Children;
		bool				m_NeedsUpdate;
		hpm::mat3			m_LocalMat;
		hpm::mat3			m_WorldMat;
		//hpm::mat4 m_SelfMatrix;
		
		//Temporary solution
		Renderer2D* m_Renderer;
		
		explicit inline Node(Node* parent, Renderer2D* renderer);
	 
	public:
		virtual ~Node() = default;

		/*
		// These methods must call appropriate methods 
		// for children after all actions have been completed.
		*/
		virtual void init() {}
		virtual void update() = 0;
		virtual void draw() {}
	
		
		inline void setParent(Node* parent);
	
		inline constexpr unsigned int getID() const noexcept;
		inline Node* getParent() const noexcept;
		inline const hpm::mat3& getTransformMat() const noexcept;
		inline const hpm::mat3& getWorldMat() const noexcept;
	
		inline void setTransform(const hpm::mat3& transform) noexcept;
		inline void makeNeedsUpdate();
		
	protected:
		inline void addChild(Node* child);

		inline void updatePosition();
		// These methods must be called in draw and update overridden methods
		inline void updateChildren();
		// This method used when parent node was updated to recalculate all children positions
		inline void forceUpdateChildren();
		inline void drawChildren();

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
