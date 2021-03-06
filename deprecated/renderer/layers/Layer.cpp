//#include <renderer/layers/Layer.h>
//
//#include <renderer/Renderer2D.h>
//#include <shading/Shader.h>
//#include <renderer/renderable/Renderable2D.h>
//
//namespace prx {
//
//	Layer::Layer(Renderer2D* renderer, Shader* shader, hpm::mat4 projectionMatrix)
//		: m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(projectionMatrix) {
//		
//		int samplerIndices[32];
//		for (int i = 0; i < 32; i++)
//			samplerIndices[i] = i;
//
//		m_Shader->bind();
//		m_Shader->setUniform("u_textures[0]", samplerIndices, 32);
//		m_Shader->setUniform("u_ProjectionMatrix", projectionMatrix);
//		m_Shader->unbind();
//	}
//
//	Layer::~Layer() {
//		delete m_Renderer;
//		for (auto* renderable : m_Renderables)
//			delete renderable;
//	}
//
//	void Layer::add(Renderable2D* renderable) {
//		m_Renderables.push_back(renderable);
//	}
//
//	void Layer::draw() {
//		m_Shader->bind();
//
//		m_Renderer->begin();
//		for (auto renderable : m_Renderables)
//			renderable->submit(m_Renderer);
//		m_Renderer->end();
//
//		m_Renderer->flush();
//
//		m_Shader->unbind();
//
//	}
//
//	//void Layer::setMaskTransformation(const hpm::mat4& matrix) {
//	//	m_Shader->bind();
//	//	m_Shader->setUniform("u_MaskMatrix", matrix);
//	//	m_Shader->unbind();
//	//}
//
//	void Layer::setProjectionMatrix(const hpm::mat4& matrix) {
//		m_ProjectionMatrix = matrix;
//		m_Shader->bind();
//		m_Shader->setUniform("u_ProjectionMatrix", matrix);
//		m_Shader->unbind();
//	}
//}
