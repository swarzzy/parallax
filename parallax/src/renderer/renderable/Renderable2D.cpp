#include "Renderable2D.h"

#include "../Renderer2D.h"

namespace prx {

	Renderable2D::Renderable2D() noexcept
		: m_Width(0),
		  m_Height(0),
		  m_Color(Renderer2D::NULL_COLOR), 
	      m_Texture(nullptr),
		  m_NormalMap(nullptr),
		  m_Reflected(false) 
	{
		setDefaultUVs();
	}

	prx::Renderable2D::Renderable2D(const hpm::vec2& size, unsigned int color, bool reflected) noexcept
		: m_Width(size.x),
		  m_Height(size.y),
		  m_Color(color), 
		  m_Texture(nullptr),
		  m_NormalMap(nullptr),
		  m_Reflected(reflected) 
	{
		setDefaultUVs();
	}

	Renderable2D::Renderable2D(float width, float height, unsigned color, bool reflected) noexcept
		: m_Width(width),
		  m_Height(height),
		  m_Color(color),
		  m_Texture(nullptr),
		  m_NormalMap(nullptr),
		  m_Reflected(reflected)
	{
		setDefaultUVs();
	}

	Renderable2D::Renderable2D(const hpm::vec2& size, TextureBase* texture, bool reflected) noexcept
		: m_Width(size.x),
		  m_Height(size.y),
		  m_Color(Renderer2D::NULL_COLOR),
		  m_Texture(texture),
		  m_NormalMap(nullptr),
		  m_Reflected(reflected) 
	{
		setDefaultUVs();
	}

	Renderable2D::Renderable2D(float width, float height, TextureBase* texture, bool reflected) noexcept
		: m_Width(width),
		  m_Height(height),
		  m_Color(Renderer2D::NULL_COLOR),
		  m_Texture(texture),
		  m_NormalMap(nullptr),
		  m_Reflected(reflected)
	{
		setDefaultUVs();
	}

	Renderable2D::Renderable2D(const hpm::vec2& size, TextureBase* texture, TextureBase* normalMap, bool reflected) noexcept 
		: m_Width(size.x),
		m_Height(size.y),
		m_Color(Renderer2D::NULL_COLOR),
		m_Texture(texture),
		m_NormalMap(normalMap),
		m_Reflected(reflected)
	{
		setDefaultUVs();
	}


	void Renderable2D::setDefaultUVs() noexcept {
		m_UVs[0] = 0.0f;
		m_UVs[1] = 0.0f;

		m_UVs[2] = 0.0f;
		m_UVs[3] = 1.0f;

		m_UVs[4] = 1.0f;
		m_UVs[5] = 1.0f;

		m_UVs[6] = 1.0f;
		m_UVs[7] = 0.0f;
	}

	void Renderable2D::setReflectDefaultUVs() noexcept {
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
