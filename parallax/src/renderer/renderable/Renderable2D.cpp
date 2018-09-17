#include <renderer/renderable/Renderable2D.h>

#include<iterator>;

#include <renderer/Renderer2D.h>

namespace prx {

	Renderable2D::Renderable2D()
		: m_Position(hpm::vec3(0.0)), m_Size(hpm::vec2(0.0)), m_Color(0xffffffff), m_Texture(nullptr) 
	{ setDefaultUVs(); }

	prx::Renderable2D::Renderable2D(hpm::vec3 position, hpm::vec2 size, unsigned int color)
		: m_Position(position), m_Size(size), m_Color(color), m_Texture(nullptr)
	{ setDefaultUVs(); }

	Renderable2D::Renderable2D(hpm::vec3 position, hpm::vec2 size, Texture* texture)
		: m_Position(position), m_Size(size), m_Color(0xffffffff), m_Texture(texture)
	{ setDefaultUVs(); }
		
	

	void Renderable2D::submit(Renderer2D* renderer) const {
		renderer->submit(*this);
	}

	void Renderable2D::setDefaultUVs() {
		m_UVs[0] = 0.0;
		m_UVs[1] = 0.0;
		m_UVs[2] = 0.0;
		m_UVs[3] = 1.0;
		m_UVs[4] = 1.0;
		m_UVs[5] = 1.0;
		m_UVs[6] = 1.0;
		m_UVs[7] = 0.0;
	}
}
