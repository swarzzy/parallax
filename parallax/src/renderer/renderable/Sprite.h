#pragma once
#ifndef _PARALLAX_RENDERER_RENDERABLE_SPRITE_H_
#define _PARALLAX_RENDERER_RENDERABLE_SPRITE_H_

#include "Renderable2D.h"

namespace prx {
	
	class TextureBase;

	enum class SpriteWrapMode {
		STRETCHING,
		TEXTURE_WRAPPING
	};

	class Sprite: public Renderable2D {
		PRX_DISALLOW_COPY_AND_MOVE(Sprite)
	private:
		SpriteWrapMode m_WrapMode;
	public:
		Sprite(const hpm::vec2& size, unsigned int color);
		Sprite(const hpm::vec2& size, TextureBase* texture);
		Sprite(float width, float height, unsigned int color);
		Sprite(float width, float height, TextureBase* texture);

		void setWrapMode(SpriteWrapMode mode);

		void reflect(bool reflect) noexcept override;

		void submit(Renderer2D* renderer, const hpm::mat3& worldMatrix, float depth) override;

	private:
		// Reimplementing all that stuff here because of mess on renderable 
		void setUV();
		void setReflectedUV();
		void setQuadUV();
		void setReflectedQuadUV();
	};
}
#endif


