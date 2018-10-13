#pragma once
#ifndef _GROUP_H_
#define _GROUP_H_

#include <vector>

#include "Renderable2D.h"

namespace prx {
	class Group : public Renderable2D {
	private:
		std::vector<Renderable2D*> m_Renderables;
		hpm::mat3 m_TransformationMatrix;
	public:
		Group(const hpm::mat3& transformation);
		~Group();
		void add(Renderable2D* renderable);
		void submit(Renderer2D* renderer) const override;

		inline void setTransformationMatrix(const hpm::mat3& transformation) { m_TransformationMatrix = transformation; }
	};
}
#endif