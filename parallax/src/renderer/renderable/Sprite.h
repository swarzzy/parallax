#pragma once
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Renderable2D.h"

namespace prx {
		class Sprite: public Renderable2D {
		private:

		public:
			Sprite(hpm::vec3 position, hpm::vec2 size, unsigned int color);
			Sprite(hpm::vec3 position, hpm::vec2 size, Texture& texture);
		};
	}
#endif


