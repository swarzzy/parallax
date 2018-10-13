#include <renderer/renderable/Sprite.h>

namespace prx {

	prx::Sprite::Sprite(hpm::vec2 position, hpm::vec2 size, unsigned int color) 
		: Renderable2D(position, size, color) {}

	Sprite::Sprite(hpm::vec2 position, hpm::vec2 size, TextureBase* texture)
		: Renderable2D(position, size, texture) {}

	Sprite::Sprite(float x, float y, float width, float height, unsigned color) 
		: Renderable2D(hpm::vec2(x, y), hpm::vec2(width, height), color) {}

	Sprite::Sprite(float x, float y, float width, float height, TextureBase* texture) 
		: Renderable2D(hpm::vec2(x, y), hpm::vec2(width, height), texture) {}

	Sprite::Sprite(float width, float height, unsigned color)
		: Renderable2D(hpm::vec2(0.0f), hpm::vec2(width, height), color) {}

	Sprite::Sprite(float width, float height, TextureBase* texture)
		: Renderable2D(hpm::vec2(0.0f), hpm::vec2(width, height), texture) {}
}
