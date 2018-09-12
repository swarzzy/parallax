#pragma once
#ifndef _LAYER_H_
#define _LAYER_H_

#include "../Renderer2D.h"
#include "../renderable/Renderable2D.h"


namespace prx {
	class Layer {
	protected:
				   Renderer2D*	m_Renderer;
	std::vector<Renderable2D*>	m_Renderables;
	   std::shared_ptr<Shader>	m_Shader;
	                 hpm::mat4	m_ProjectionMatrix;
	protected:
		Layer(Renderer2D* renderer, std::shared_ptr<Shader> shader, hpm::mat4 projectionMatrix);
	public:
		virtual ~Layer();
		virtual void add(Renderable2D* renderable);
		virtual void draw();
	};
}
#endif

