#pragma once
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Renderable2D.h"

namespace prx {
	
	class TextureBase;

	class Sprite: public Renderable2D {
		PRX_DISALLOW_COPY_AND_MOVE(Sprite)
		public:
			Sprite(const hpm::vec2& size, unsigned int color);
			Sprite(const hpm::vec2& size, const TextureBase* texture);
			Sprite(float width, float height, unsigned int color);
			Sprite(float width, float height, const TextureBase* texture);

			void submit(Renderer2D* renderer, const hpm::mat3& worldMatrix, float depth) override;
		};
	}
#endif


