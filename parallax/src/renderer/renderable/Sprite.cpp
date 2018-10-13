#include <renderer/renderable/Sprite.h>
#include <renderer/Renderer2D.h>

namespace prx {

	Sprite::Sprite(const hpm::vec2& size, unsigned int color) 
		: Renderable2D(size, color) {}

	Sprite::Sprite(const hpm::vec2& size, const TextureBase* texture)
		: Renderable2D(size, texture) {}

	Sprite::Sprite(float width, float height, unsigned color) 
		: Renderable2D(width, height, color) {}

	Sprite::Sprite(float width, float height, const TextureBase* texture) 
		: Renderable2D(width, height, texture) {}

	void Sprite::submit(Renderer2D* renderer, const hpm::mat3& worldMatrix) {
		if (m_Texture == nullptr)
			renderer->drawRect(worldMatrix, m_Width, m_Height, m_Color);
		else
			renderer->drawRect(worldMatrix, m_Width, m_Height, m_Texture);
	}
}
