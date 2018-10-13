#pragma once
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Renderable2D.h"

namespace prx {
		class Sprite: public Renderable2D {
		public:
			Sprite(hpm::vec2 position, hpm::vec2 size, unsigned int color);
			Sprite(hpm::vec2 position, hpm::vec2 size, TextureBase* texture);
			Sprite(float x, float y, float width, float height, unsigned int color);
			Sprite(float x, float y, float width, float height, TextureBase* texture);
			// Sets position as (0.0, 0.0) automatically
			Sprite(float width, float height, unsigned int color);
			Sprite(float width, float height, TextureBase* texture);

		};
	}
#endif


