#pragma once
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "renderable/Renderable2D.h"

namespace prx {
	class Renderer2D {
	protected:
		std::vector<hpm::mat4> m_TransformationStack;
		// TODO: make this matrix pointer
		hpm::mat4 m_TransformationStackBack;
	protected:
		Renderer2D();
	public:
		void push(const hpm::mat4& matrix);
		void pop();

		virtual void drawString(std::string_view text, hpm::vec3 position, hpm::vec4 color) {};

		virtual void begin() {};
		virtual void submit(const Renderable2D& renderable) = 0;
		virtual void end() {};
		virtual void flush() = 0;
	};
}
#endif