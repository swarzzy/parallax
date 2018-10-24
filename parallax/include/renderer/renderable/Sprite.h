#pragma once
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Renderable2D.h"

namespace prx {
	
	class TextureBase;

	class Sprite: public Renderable2D {
		public:
			Sprite(const hpm::vec2& size, unsigned int color);
			Sprite(const hpm::vec2& size, const TextureBase* texture);
			Sprite(float width, float height, unsigned int color);
			Sprite(float width, float height, const TextureBase* texture);

			void submit(Renderer2D* renderer, const hpm::mat3& worldMatrix, float depth) override;

		public:
			Sprite(const Sprite& other) = delete;
			Sprite(const Sprite&& other) = delete;
			Sprite(Sprite&& other) = delete;
			const Sprite& operator=(const Sprite& other) = delete;
			const Sprite& operator=(const Sprite&& other) = delete;
			const Sprite& operator=(Sprite&& other) = delete;
		};
	}
#endif


