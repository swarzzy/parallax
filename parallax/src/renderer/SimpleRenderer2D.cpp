#include "SimpleRenderer2D.h"

#ifdef PARALLAX_USE_DEPRECATED_FEATURES

#include "../utils/error_handling/GLErrorHandler.h"

namespace prx {

	SimpleRenderer2D::SimpleRenderer2D() {
		
	}

	void prx::SimpleRenderer2D::submit(const Renderable2D& renderable) {
		m_RendererQueue.push_back(static_cast<const StaticSprite*>(&renderable));
	}

	void SimpleRenderer2D::flush() {
		while (!m_RendererQueue.empty()) {
			const StaticSprite* sprite = m_RendererQueue.front();
			m_RendererQueue.pop_front();

			sprite->getVAO().Bind();
			sprite->getShader()->bind();
			sprite->getShader()->setUniform("u_ModelMatrix", hpm::mat4::translation(sprite->getPosition()));
				
			GLCall(glDrawElements(GL_TRIANGLES, sprite->getIndexCount(), GL_UNSIGNED_INT, nullptr));

			sprite->getShader()->unbind();
			sprite->getVAO().Unbind();
		}
	}
}
#endif
