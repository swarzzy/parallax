#include "Sprite.h"

namespace prx {

	prx::Sprite::Sprite(hpm::vec3 position, hpm::vec2 size, hpm::vec4 color) 
		: Renderable2D(position, size, color) {}

	Sprite::Sprite(hpm::vec3 position, hpm::vec2 size, Texture& texture) 
		: Renderable2D(position, size, texture) {}
}
