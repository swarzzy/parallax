#pragma once
#ifndef _BATCHRENDERER2D_H_
#define _BATCHRENDERER2D_H_

#include <vector>

#include "Renderer2D.h"
#include "buffer/IndexBuffer.h"

namespace prx {
	
	constexpr unsigned int BATCH_RENDERER_MAX_SPRITES		=	60000;
	constexpr unsigned int BATCH_RENDERER_VERTEX_SIZE		=	sizeof(VertexData);
	constexpr unsigned int BATCH_RENDERER_SPRITE_SIZE		=	BATCH_RENDERER_VERTEX_SIZE * 4;
	constexpr unsigned int BATCH_RENDERER_INDICES_SIZE		=	BATCH_RENDERER_MAX_SPRITES * 6;
	constexpr unsigned int BATCH_RENDERER_BUFFER_SIZE		=	BATCH_RENDERER_SPRITE_SIZE * BATCH_RENDERER_MAX_SPRITES;
	constexpr unsigned int BATCH_RENDERER_MAX_TEXTURE_SLOTS =	32;

	constexpr unsigned int BATCH_RENDERER_SHADER_VERTEX_INDEX	=	0;
	constexpr unsigned int BATCH_RENDERER_SHADER_UV_INDEX		=	1;
	constexpr unsigned int BATCH_RENDERER_SHADER_TEXID_INDEX	=	2;
	constexpr unsigned int BATCH_RENDERER_SHADER_COLOR_INDEX	=	3;

	
	class BatchRenderer2D : public Renderer2D {
	private:

		unsigned int				 m_VAO;
		unsigned int				 m_VBO;
		std::unique_ptr<IndexBuffer> m_IBO;
		std::vector<unsigned int>	 m_TextureSlots;
		int							 m_IndexCount;
		VertexData*					 m_Buffer;
		std::map<unsigned short, unsigned short> m_TextureBindings;

	public:
		BatchRenderer2D();
		~BatchRenderer2D();

		void begin() override;
		void drawString(std::string_view text, hpm::vec3 position, const Font* font, unsigned int color, Renderable2D* label = nullptr) override;
		void submit(const Renderable2D& renderable) override;
		void end() override;
		void flush() override;

	private:
		void init();
	};
}
#endif
