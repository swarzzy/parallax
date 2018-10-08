#include <renderer/Renderer2D.h>

#include <utils/log/Log.h>
#include <textures/Texture.h>

namespace prx {

	Renderer2D::Renderer2D(RenderTarget rendertarget, FrameBuffer2D* frameBuffer)
		: m_Mask(nullptr), m_RenderTarget(rendertarget), m_FrameBuffer(frameBuffer) {
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
			Log::message(LOG_LEVEL::LOG_WARN, "RENDERER2D: Trying to pop matrix from empty transformation stack.");
	}

	void Renderer2D::defaultMask() {
		unsigned char maskData[3] = { 255, 255, 255 };
		m_Mask = new Texture(maskData, 1, 1, TextureFormat::RGB);
	}
}
