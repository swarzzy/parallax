#include <renderer/renderable/Group.h>
#include <renderer/Renderer2D.h>

namespace prx {

	Group::Group(const hpm::mat4 & transformation) 
		: m_TransformationMatrix(transformation){
	}

	Group::~Group() {
		for (auto* renderable : m_Renderables)
			delete renderable;
	}

	void Group::add(Renderable2D* renderable) {
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
