#include "StaticSprite.h"

namespace prx {

	StaticSprite::StaticSprite() 
		: Renderable2D(hpm::vec3(0.0), hpm::vec2(0.0), hpm::vec4(0.0)), m_Shader(nullptr) {}

	StaticSprite::StaticSprite(hpm::vec3 position, hpm::vec2 size, hpm::vec4 color, Shader* shader)
		: Renderable2D(position, size, color), m_Shader(shader) {

		m_VertexArray = std::make_shared<VertexArray>();

		float vertices[] = {
			0.0, 0.0, 0.0, color.r, color.g, color.b, color.a, 0.0, 0.0,
			0.0, size.y, 0.0, color.r, color.g, color.b, color.a,0.0, 1.0,
			size.x, size.y, 0.0, color.r, color.g, color.b, color.a,1.0, 1.0,
			size.x, 0, 0, color.r, color.g, color.b, color.a, 1.0, 0.0
		};
		unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };
		m_IndexCount = std::size(indices);

		auto buffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
		auto indexBuffer = std::make_unique<IndexBuffer>(indices, m_IndexCount);

		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(4);
		layout.Push<float>(2);

		m_VertexArray->AddBuffer(*buffer, layout, *indexBuffer);

	}
}
