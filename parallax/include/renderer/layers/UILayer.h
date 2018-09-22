#pragma once
#ifndef _PARALLAX_LAYERS_UI_LAYER_H_
#define _PARALLAX_LAYERS_UI_LAYER_H__

#include "Layer.h"
#include "../../window/Window.h"
#include "../renderable/UI/UIWidget.h"

namespace prx {
	class UILayer : public Layer {
	private:
		Window* m_Window;
		std::vector<UIWidget*>	m_Widgets;
		std::vector<UIWidget*>	m_ClickableWidgets;
	
	public:
		UILayer(Window* window);
		~UILayer();

		void addWidget(UIWidget* widget);

		void update();

		void draw() override;

		void updateProjectionMatrix();

	private:
		void mouseTest();
	};
}
#endif
