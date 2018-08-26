#include "Group.h"
#include "../Renderer2D.h"
namespace prx {

	Group::Group(const hpm::mat4 & transformation) 
		: m_TransformationMatrix(transformation){
	}

	void Group::add(Renderable2D* renderable) {
		// TODO: Make it emplace_back
		m_Renderables.push_back(renderable);
	}

	void Group::submit(Renderer2D* renderer) const {
		renderer->push(m_TransformationMatrix);

		for (auto renderable : m_Renderables) {
			renderable->submit(renderer);
		}

		renderer->pop();
	}
}