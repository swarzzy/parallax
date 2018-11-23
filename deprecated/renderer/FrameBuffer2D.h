#pragma once
#ifndef _PARALLAX_RENDERER_FRAMEBUFFER2D_H_
#define _PARALLAX_RENDERER_FRAMEBUFFER2D_H_
#include "FrameBufferBase.h"
#include "../textures/Texture.h"

namespace prx {
	class FrameBuffer2D : public FrameBufferBase {
	private:
		Texture*	 m_Texture;
		unsigned int m_RBO;
		bool		 m_Valid;
	public:
		FrameBuffer2D(unsigned int width, unsigned int height);
		FrameBuffer2D(const FrameBuffer2D& other) = delete;
		FrameBuffer2D(FrameBuffer2D&& other) noexcept;

		~FrameBuffer2D();

		void clear() override;
		bool validate() override;

		// Might be unsafe to return a raw pointer
		inline constexpr Texture* getTexture() const { return m_Texture; };

	private:
		void init();

	public:
		FrameBuffer2D& operator=(const FrameBuffer2D& other) = delete;
		FrameBuffer2D& operator=(FrameBuffer2D&& other) = delete;
		FrameBuffer2D& operator=(const FrameBuffer2D&& other) = delete;
		bool operator==(const FrameBuffer2D& other);
		bool operator!=(const FrameBuffer2D& other);
	};
}
#endif
