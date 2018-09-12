#include "Sprite.h"

namespace prx {

	prx::Sprite::Sprite(hpm::vec3 position, hpm::vec2 size, unsigned int color) 
		: Renderable2D(position, size, color) {}

	Sprite::Sprite(hpm::vec3 position, hpm::vec2 size, std::shared_ptr<Texture> texture)
		: Renderable2D(position, size, texture) {}
}
