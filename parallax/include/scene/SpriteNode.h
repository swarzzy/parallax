#pragma once
#include "Node.h"
#include "../renderer/renderable/Sprite.h"
#include "../renderer/renderable/Group.h"

namespace prx {
	class SpriteNode final : public Node {
	private:
		Sprite* m_Sprite;

	public:
		SpriteNode(float x, float y,
				   float width, float height, 
				   unsigned int color, 
				   Node* parent = nullptr);

		SpriteNode(float x, float y,
				   float width, float height,
				   TextureBase* texture,
				   Node* parent = nullptr);

		SpriteNode(float width, float height,
				   unsigned int color,
				   Node* parent = nullptr);
		
		SpriteNode(float width, float height,
				   TextureBase* texture,
				   Node* parent = nullptr);
		
		~SpriteNode();

		void update() override;
		void draw(Renderer2D* renderer) override;

		inline const Sprite& getSprite() const noexcept;

	public:
		SpriteNode(const SpriteNode& other) = delete;
		SpriteNode(const SpriteNode&& other) = delete;
		SpriteNode(SpriteNode&& other) = delete;
		SpriteNode& operator=(const SpriteNode& other) = delete;
		SpriteNode& operator=(const SpriteNode&& other) = delete;
		SpriteNode& operator=(SpriteNode&& other) = delete;
	};
	
	inline const Sprite& SpriteNode::getSprite() const noexcept {
		return *m_Sprite;
	}

}
