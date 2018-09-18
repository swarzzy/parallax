#pragma once
#ifndef _LAYER_H_
#define _LAYER_H_

#include <vector>
#include <hypermath.h>

namespace prx {

	class Renderer2D;
	class Renderable2D;
	class Shader;

	class Layer {
	protected:
				   Renderer2D*	m_Renderer;
	std::vector<Renderable2D*>	m_Renderables;
						Shader*	m_Shader;
	                 hpm::mat4	m_ProjectionMatrix;
	protected:
		Layer(Renderer2D* renderer, Shader* shader, hpm::mat4 projectionMatrix);
	public:
		virtual ~Layer();
		virtual void add(Renderable2D* renderable);
		virtual void draw();
	};
}
#endif

