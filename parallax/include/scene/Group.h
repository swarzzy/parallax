#pragma once

#include "../Common.h"
#include "Node.h"

namespace prx {
	class Group final : public Node {
			
		PRX_DISALLOW_COPY_AND_MOVE(Group)

	public:
		Group(Node* parent = 0) : Node(parent) {};
		~Group() {};
	};
}