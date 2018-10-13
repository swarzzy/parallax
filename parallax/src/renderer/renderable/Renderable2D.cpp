#include <renderer/renderable/Renderable2D.h>

#include <renderer/Renderer2D.h>

namespace prx {

	Renderable2D::Renderable2D()
		: m_Position(hpm::vec2(0.0)), m_Size(hpm::vec2(0.0)), 
		m_Color(0xffffffff), m_Texture(nullptr), m_Reflected(false) 
	{ setDefaultUVs(); }

	prx::Renderable2D::Renderable2D(const hpm::vec2& position, const hpm::vec2& size, unsigned int color, bool reflected)
		: m_Position(position), m_Size(size), m_Color(color), m_Texture(nullptr), m_Reflected(reflected)
	{ setDefaultUVs(); }

	Renderable2D::Renderable2D(const hpm::vec2& position, const hpm::vec2& size, TextureBase* texture, bool reflected)
		: m_Position(position), m_Size(size), m_Color(0xffffffff), m_Texture(texture), m_Reflected(reflected)
	{ setDefaultUVs(); }
		
	

	void Renderable2D::submit(Renderer2D* renderer) const {
		renderer->submit(*this);
	}

	void Renderable2D::setDefaultUVs() {
		m_UVs[0] = 0.0f;
		m_UVs[1] = 0.0f;

		m_UVs[2] = 0.0f;
		m_UVs[3] = 1.0f;

		m_UVs[4] = 1.0f;
		m_UVs[5] = 1.0f;

		m_UVs[6] = 1.0f;
		m_UVs[7] = 0.0f;
	}

	void Renderable2D::setReflectDefaultUVs() {
		m_UVs[0] = 1.0f;
		m_UVs[1] = 0.0f;

		m_UVs[2] = 1.0f;
		m_UVs[3] = 1.0f;

		m_UVs[4] = 0.0f;
		m_UVs[5] = 1.0f;

		m_UVs[6] = 0.0f;
		m_UVs[7] = 0.0f;
	}
}
