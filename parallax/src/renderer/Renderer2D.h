#pragma once

#include <hypermath.h>
#include "../textures/Texture.h"

namespace prx {
	
	class Renderable2D;
	class FrameBuffer2D;
	class Font;

	struct VertexData {
		hpm::vec2		vertex;
		float			depth;
		hpm::vec2		UVs;
		float			texID;
		unsigned int	color;
	};

	enum class RenderTarget {
		SCREEN,
		BUFFER
	};

	class Renderer2D {
	protected:
		inline static const float	 QUAD_DEFAULT_POSITION_X = 0.0f;
		inline static const float	 QUAD_DEFAULT_POSITION_Y = 0.0f;
		inline static const unsigned NULL_COLOR = 0xffffffff;

		inline static const hpm::mat4 DEFAULT_PROJECTION_MATRIX = 
			hpm::mat4::ortho(0.0f, 800.0f, 600.0f, 0.0f, -10.0f, 10.0f);
		inline static const char* DEFAULT_MASK_NAME = "parallax_default_renderer_mask_name";

	protected:
		Texture*				m_Mask;
		RenderTarget			m_RenderTarget;
		FrameBuffer2D*			m_FrameBuffer;

	protected:
		inline Renderer2D(RenderTarget rendertarget = RenderTarget::SCREEN, FrameBuffer2D* frameBuffer = nullptr) noexcept;

	public:
		virtual ~Renderer2D() noexcept {};

		virtual void init() {};
		virtual void destroy() {};

		virtual void setMask(Texture* mask) noexcept;
		inline virtual void defaultMask() noexcept;

		virtual void setProjectionMatrix(const hpm::mat4& projMatrix) = 0;

		virtual void setRenderTarget(RenderTarget target) = 0;
		virtual void setFrameBuffer(FrameBuffer2D* framebuffer) = 0;
		
		virtual void begin() {};

		virtual void drawRect(const hpm::vec2& position, float depth, const hpm::vec2& size, unsigned int color = 0xffffffff) = 0;
		virtual void drawRect(const hpm::vec2& position, float depth, const hpm::vec2& size, const TextureBase* texture, bool reflect = false) = 0;
		virtual void drawRect(const hpm::mat3& worldMat, float depth, float width, float height, unsigned int color = 0xffffffff) = 0;
		virtual void drawRect(const hpm::mat3& worldMat, float depth, float width, float height, const TextureBase* texture, bool reflect = false) = 0;

		virtual void drawRenderable(const hpm::mat3& worldMat, float depth, const Renderable2D* renderable) = 0;

		virtual void drawString(std::string_view text, const hpm::mat3& worldMatrix, float depth, const Font* font, unsigned int color) {};
		virtual void drawString(std::string_view text, const hpm::vec2& position, float depth, const Font* font, unsigned int color) {};

		virtual void end() {};
		virtual void flush() = 0;

	public:
		Renderer2D(const Renderer2D& other) = delete;
		Renderer2D(const Renderer2D&& other) = delete;
		Renderer2D(Renderer2D&& other) = delete;
		Renderer2D& operator=(const Renderer2D& other) = delete;
		Renderer2D& operator=(const Renderer2D&& other) = delete;
		Renderer2D& operator=(Renderer2D&& other) = delete;
	};

	inline Renderer2D::Renderer2D(RenderTarget rendertarget, FrameBuffer2D* frameBuffer) noexcept
		: m_Mask(nullptr), m_RenderTarget(rendertarget), m_FrameBuffer(frameBuffer)
	{}

	inline void Renderer2D::defaultMask() noexcept {
		unsigned char maskData[3] = { 255, 255, 255 };
		m_Mask = new Texture(maskData, 1, 1, TextureFormat::RGB);
		m_Mask->init();
	}

	inline void Renderer2D::setMask(Texture* mask) noexcept {
		m_Mask = mask;
	}
}