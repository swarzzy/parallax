//#pragma once
//#ifndef _PARALLAX_RENDERER_UI_GROUP_H_
//#define _PARALLAX_RENDERER_UI_GROUP_H_
//
//#include <vector>
//
//#include "UIWidget.h"
//
//namespace prx {
//	class UIGroup : public UIWidget {
//	private:
//		std::vector<UIWidget*> m_Widgets;
//		hpm::mat4 m_TransformationMatrix;
//	public:
//		UIGroup(const hpm::mat4& transformation);
//		~UIGroup();
//
//		void add(UIWidget* widget);
//
//		void submit(Renderer2D* renderer) const override;
//
//		void update() override;
//
//		inline void setTransformationMatrix(const hpm::mat4& transformation) {
//			m_TransformationMatrix = transformation;
//		}
//	};
//}
//#endif
