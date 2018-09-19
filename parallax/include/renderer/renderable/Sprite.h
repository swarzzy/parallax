#pragma once
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Renderable2D.h"

namespace prx {
		class Sprite: public Renderable2D {
		public:
			Sprite(hpm::vec3 position, hpm::vec2 size, unsigned int color);
			Sprite(hpm::vec3 position, hpm::vec2 size, TextureBase* texture);

			inline void setSize(hpm::vec2 size) { m_Size = size; };
			inline void setTexture(TextureBase* texture) { if (m_Texture != nullptr) m_Texture = texture; };
		};
	}
#endif


