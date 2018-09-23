#pragma once
#ifndef _PARALLAX_LAYERS_UI_LAYER_H_
#define _PARALLAX_LAYERS_UI_LAYER_H__

#include "Layer.h"
#include "../../window/Window.h"
#include "../renderable/UI/UIClickable.h"


namespace prx {
	class UILayer : public Layer {
	private:
		std::vector<UIWidget*>	m_Widgets;
	
	public:
		UILayer();
		~UILayer();

		void add(Renderable2D* renderable) override;

		void draw() override;

		void update();

		void updateProjectionMatrix();

	private:
		void mouseTest();
	};
}
#endif
