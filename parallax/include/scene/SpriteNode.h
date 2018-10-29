#pragma once
#include "Node.h"
#include "../renderer/renderable/Sprite.h"
#include "../renderer/renderable/Group.h"
#include "../Common.h"
#include "../resources/ResourceHandler.h"
#include "../textures/Texture.h"

namespace prx {

	class SpriteNode final : public Node {
		PRX_DISALLOW_COPY_AND_MOVE(SpriteNode)
	private:
		Sprite* m_Sprite;
		ResourceHandler<Texture> m_Texture;

		SpriteNode(float x, float y,
				   float width, float height, 
				   unsigned int color,
				   Scene* scene,
				   Node* parent = nullptr);

		SpriteNode(float x, float y,
				   float width, float height,
				   ResourceHandler<Texture> texture,
				   Scene* scene,
				   Node* parent = nullptr);

		SpriteNode(float width, float height,
				   unsigned int color,
				   Scene* scene,
				   Node* parent = nullptr);
		
		SpriteNode(float width, float height,
				   ResourceHandler<Texture> texture,
				   Scene* scene,
				   Node* parent = nullptr);
	public:
		friend class Scene;
		
		~SpriteNode();

		inline const Sprite& getSprite() const noexcept;
		inline ResourceHandler<Texture> getTexture() const noexcept;

	private:
		void initInternal() override;
		void drawInternal(Renderer2D* renderer) override;
		void destroyInternal() override;
	};
	
	inline const Sprite& SpriteNode::getSprite() const noexcept {
		return *m_Sprite;
	}

	inline ResourceHandler<Texture> SpriteNode::getTexture() const noexcept {
		return m_Texture;
	}

}
