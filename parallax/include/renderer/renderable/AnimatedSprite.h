#pragma once
#ifndef _PARALLAX_RENDERER_RENDERABLES_ANIMATED_SPRITE_H_
#define _PARALLAX_RENDERER_RENDERABLES_ANIMATED_SPRITE_H_
#include "Sprite.h"
#include "../../textures/SpriteSheet.h"

namespace prx {
	
	class AnimatedSprite : public Sprite {
	public:
		AnimatedSprite(hpm::vec3 position, hpm::vec2 size, SpriteSheet* texture)
			: Sprite(position, size, texture) {};

		inline const float* getUVs() const override {
			
			TexCoords tc = static_cast<SpriteSheet*>(m_Texture)->getTexCoords();
			
			m_UVs[0] = tc.lbX;
			m_UVs[1] = tc.lbY;
			m_UVs[2] = tc.ltX;
			m_UVs[3] = tc.ltY;
			m_UVs[4] = tc.rtX;
			m_UVs[5] = tc.rtY;
			m_UVs[6] = tc.rbX;
			m_UVs[7] = tc.rbY;
			return m_UVs;
		};
	};
}
#endif
