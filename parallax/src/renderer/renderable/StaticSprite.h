#pragma once
#ifndef _STATICSPRITE_H_
#define _STATICSPRITE_H_

#include "Renderable2D.h"

namespace prx {
	class StaticSprite : public Renderable2D {
	private:
		unsigned int m_IndexCount;
		std::shared_ptr<VertexArray> m_VertexArray;
		Shader* m_Shader;
	public:
		
		StaticSprite();
		StaticSprite(hpm::vec3 position, hpm::vec2 size, hpm::vec4 color, Shader* shader);
		
		inline const VertexArray& getVAO() const { return *m_VertexArray; };
		inline unsigned int getIndexCount() const { return m_IndexCount; };
		inline Shader* getShader() const { return m_Shader; };
	};
}
#endif 