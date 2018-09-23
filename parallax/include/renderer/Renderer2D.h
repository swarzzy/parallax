#pragma once
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <vector>

#include "renderable/Renderable2D.h"
#include "../Fonts/Font.h";

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

		virtual void drawString(std::string_view text, hpm::vec3 position, const Font* font, unsigned int color) {};

		virtual void begin() {};
		virtual void submit(const Renderable2D& renderable) = 0;
		virtual void end() {};
		virtual void flush() = 0;

		inline const hpm::mat4 getTransformationStackBack() const {
			return m_TransformationStackBack;
		}
	};
}
#endif