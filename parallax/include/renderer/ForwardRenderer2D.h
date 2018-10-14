#pragma once

#include <vector>

#include "Renderer2D.h"

namespace prx {
	
	class IndexBuffer;
	class FrameBuffer2D;
	
	class ForwardRenderer2D final : public Renderer2D {
	public:
		const unsigned int	MAX_RENDERABLES		= 60000;
		const unsigned int	VERTEX_SIZE			= sizeof(VertexData);
		const unsigned int	RENDERABLE_SIZE		= VERTEX_SIZE * 4;
		const unsigned int	INDEX_BUFFER_SIZE	= MAX_RENDERABLES * 6;
		const unsigned int	BUFFER_SIZE			= RENDERABLE_SIZE * MAX_RENDERABLES;
		const unsigned int	MAX_TEXTURE_SLOTS	= 32 - 1; // Mask hold the last slot

		const unsigned int SHADER_VERTEX_INDEX	= 0;
		const unsigned int SHADER_UV_INDEX		= 1;
		const unsigned int SHADER_TEXID_INDEX	= 2;
		const unsigned int SHADER_COLOR_INDEX	= 3;

	private:
		inline static const float	 EMPTY_TEXTURE_SLOT	= 0.0f;

		unsigned int				m_VAO;
		unsigned int				m_VBO;
		IndexBuffer*				m_IBO;
		std::vector<unsigned int>	m_TextureSlots;
		int							m_IndexCount;
		VertexData*					m_Buffer;

	public:
		ForwardRenderer2D(RenderTarget rendertarget = RenderTarget::SCREEN);
		~ForwardRenderer2D();

		void begin() override;

		void drawRect(const hpm::vec2& position, const hpm::vec2& size, unsigned int color = 0xffffffff) override;
		void drawRect(const hpm::vec2& position, const hpm::vec2& size, const TextureBase* texture, bool reflect = false) override;
		void drawRect(const hpm::mat3& worldMat, float width, float height, unsigned int color = 0xffffffff) override;
		void drawRect(const hpm::mat3& worldMat, float width, float height, const TextureBase* texture, bool reflect = false) override;

		void drawRenderable(const hpm::mat3& worldMat, const Renderable2D* renderable);

		void drawString(std::string_view text, const hpm::mat3& worldMatrix, const Font* font, unsigned int color) override;
		void drawString(std::string_view text, const hpm::vec2& position, const Font* font, unsigned int color) override;
	
		void end() override;
		void flush() override;

		void setFrameBuffer(FrameBuffer2D* framebuffer) override;
		void setRenderTarget(RenderTarget target) override;

	private:
		void init();
		float submitTexture(unsigned texID);
	};
}