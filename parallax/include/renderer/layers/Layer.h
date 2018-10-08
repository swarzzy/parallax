#pragma once
#ifndef _LAYER_H_
#define _LAYER_H_

#include <vector>
#include <hypermath.h>
#include "../Renderer2D.h"

namespace prx {

	class Renderable2D;
	class Shader;
	class Texture;

	class Layer {
	protected:
				   Renderer2D*	m_Renderer;
	std::vector<Renderable2D*>	m_Renderables;
						Shader*	m_Shader;
	                 hpm::mat4	m_ProjectionMatrix;
	protected:
		Layer(Renderer2D* renderer, Shader* shader, hpm::mat4 projectionMatrix);
		Layer(const Layer* other) = delete;
		Layer& operator=(const Layer& other) = delete;
	public:
		virtual ~Layer();

		virtual void add(Renderable2D* renderable);
		virtual void draw();

		// TODO: It`s temporary solution
		inline Renderer2D* getRenderer() { return m_Renderer; }
		
		inline void setMask(Texture* mask) { m_Renderer->setMask(mask); }

		void setMaskTransformation(const hpm::mat4& matrix);
		void setProjectionMatrix(const hpm::mat4& matrix);
	};
}
#endif

