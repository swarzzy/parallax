#include <renderer/renderable/Sprite.h>

namespace prx {

	prx::Sprite::Sprite(hpm::vec3 position, hpm::vec2 size, unsigned int color) 
		: Renderable2D(position, size, color) {}

	Sprite::Sprite(hpm::vec3 position, hpm::vec2 size, TextureBase* texture)
		: Renderable2D(position, size, texture) {}

	Sprite::Sprite(float x, float y, float z, float width, float height, unsigned color) 
		: Renderable2D(hpm::vec3(x, y, z), hpm::vec2(width, height), color) {}

	Sprite::Sprite(float x, float y, float z, float width, float height, TextureBase* texture) 
		: Renderable2D(hpm::vec3(x, y, z), hpm::vec2(width, height), texture) {}

	Sprite::Sprite(float width, float height, unsigned color)
		: Renderable2D(hpm::vec3(0.0f), hpm::vec2(width, height), color) {}

	Sprite::Sprite(float width, float height, TextureBase* texture)
		: Renderable2D(hpm::vec3(0.0f), hpm::vec2(width, height), texture) {}
}
