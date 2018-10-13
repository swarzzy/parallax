#pragma once
#ifndef _BATCHRENDERER2D_H_
#define _BATCHRENDERER2D_H_

#include <vector>

#include "Renderer2D.h"
#include "buffer/IndexBuffer.h"
#include "FrameBuffer2D.h"


namespace prx {
	
	constexpr unsigned int BATCH_RENDERER_MAX_SPRITES			=	60000;
	constexpr unsigned int BATCH_RENDERER_VERTEX_SIZE			=	sizeof(VertexData);
	constexpr unsigned int BATCH_RENDERER_SPRITE_SIZE			=	BATCH_RENDERER_VERTEX_SIZE * 4;
	constexpr unsigned int BATCH_RENDERER_INDICES_SIZE			=	BATCH_RENDERER_MAX_SPRITES * 6;
	constexpr unsigned int BATCH_RENDERER_BUFFER_SIZE			=	BATCH_RENDERER_SPRITE_SIZE * BATCH_RENDERER_MAX_SPRITES;
	constexpr unsigned int BATCH_RENDERER_MAX_TEXTURE_SLOTS		=	32 - 1; // Mask hold the last slot

	constexpr unsigned int BATCH_RENDERER_SHADER_VERTEX_INDEX	=	0;
	constexpr unsigned int BATCH_RENDERER_SHADER_UV_INDEX		=	1;
	constexpr unsigned int BATCH_RENDERER_SHADER_TEXID_INDEX	=	2;
	constexpr unsigned int BATCH_RENDERER_SHADER_COLOR_INDEX	=	3;

	
	class BatchRenderer2D final : public Renderer2D {
	private:
		inline static const float	 QUAD_DEFAULT_POSITION_X = 0.0f;
		inline static const float	 QUAD_DEFAULT_POSITION_Y = 0.0f;
		inline static const float	 EMPTY_TEXTURE_SLOT		 = 0.0f;
		inline static const unsigned EMPTY_COLOR			 = 0xffffffff;

		unsigned int				m_VAO;
		unsigned int				m_VBO;
		IndexBuffer*				m_IBO;
		std::vector<unsigned int>	m_TextureSlots;
		int							m_IndexCount;
		VertexData*					m_Buffer;

	public:
		BatchRenderer2D(RenderTarget rendertarget = RenderTarget::SCREEN);
		~BatchRenderer2D();

		void begin() override;

		void drawRect(float x, float y, float width, float height, unsigned int color = 0xffffffff) override {};
		void drawRect(float x, float y, float width, float height, const TextureBase* texture) override {};
		void drawRect(const hpm::vec2& position, const hpm::vec2& size, unsigned int color = 0xffffffff) override {};
		void drawRect(const hpm::vec2& position, const hpm::vec2& size, const TextureBase* texture) override {};
		void drawRect(const hpm::mat3& worldMat, float width, float height, unsigned int color = 0xffffffff) override;
		void drawRect(const hpm::mat3& worldMat, float width, float height, const TextureBase* texture, bool reflect = false) override;

		void drawString(std::string_view text, hpm::vec2 position, const Font* font, unsigned int color) override;
		void submit(const Renderable2D& renderable) override;
		void end() override;
		void flush() override;

		void setFrameBuffer(FrameBuffer2D* framebuffer) override;
		void setRenderTarget(RenderTarget target) override;

	private:
		void init();
	};
}
#endif
