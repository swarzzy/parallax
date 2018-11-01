#pragma once

#include "../Common.h"
#include "Node.h"

namespace prx {
	class Group final : public Node {
		PRX_DISALLOW_COPY_AND_MOVE(Group)
	public:
		Group(Scene* scene, Node* parent = 0) : Node(scene, parent) {};
		~Group() {};
	};
}