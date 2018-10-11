#pragma once
#include "Node.h"
#include "../renderer/renderable/Sprite.h"
#include "../renderer/renderable/Group.h"

namespace prx {
	class SpriteNode final : public Node {
	private:
		Group* m_Group;

	public:
		SpriteNode(float x, float y, float depth,
				   float width, float height, 
				   unsigned int color, 
				   Renderer2D* renderer, 
				   Node* parent = nullptr);

		SpriteNode(float x, float y, float depth,
				   float width, float height,
				   TextureBase* texture,
				   Renderer2D* renderer,
				   Node* parent = nullptr);

		SpriteNode(float depth,
				   float width, float height,
				   unsigned int color,
				   Renderer2D* renderer,
				   Node* parent = nullptr);
		
		SpriteNode(float depth,
				   float width, float height,
				   TextureBase* texture,
				   Renderer2D* renderer,
				   Node* parent = nullptr);
		
		~SpriteNode();

		void update() override;
		void draw() override;

	public:
		SpriteNode(const SpriteNode& other) = delete;
		SpriteNode(const SpriteNode&& other) = delete;
		SpriteNode(SpriteNode&& other) = delete;
		SpriteNode& operator=(const SpriteNode& other) = delete;
		SpriteNode& operator=(const SpriteNode&& other) = delete;
		SpriteNode& operator=(SpriteNode&& other) = delete;
	};
}
