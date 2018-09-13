#include "Renderer2D.h"

namespace prx {

	Renderer2D::Renderer2D() {
		m_TransformationStack.emplace_back(1.0f);
		m_TransformationStackBack = hpm::mat4::identity();
	
	}

	void Renderer2D::push(const hpm::mat4& matrix) {
		m_TransformationStackBack = m_TransformationStack.back() * matrix;
		m_TransformationStack.push_back(m_TransformationStackBack);
	}

	void Renderer2D::pop() {
		if (m_TransformationStack.size() > 1) {
			m_TransformationStack.pop_back();
			m_TransformationStackBack = m_TransformationStack.back();
		}
		else
			Log::message("RENDERER2D: Trying to pop matrix from empty transformation stack.", LOG_WARNING);
	}
}
