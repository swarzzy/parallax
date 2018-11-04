#pragma once

#include <parallax.h>
#include "ext/imgui/imgui.h"

class TestWidget : public prx::ImGUIWidget{
private:
public:
	TestWidget() : ImGUIWidget() {
	}

	void show() override {
		ImGui::Begin("DEBUG");
		ImGui::Text("%d fps %d ups", prx::Application::getInstance()->getFPS(), Application::getInstance()->getUPS());
		ImGui::End();
	}
};
