#pragma once

#include "ImGUIWidget.h"
#include <string>

namespace prx {
	class SliderFloat final : public ImGuiWidget {
	private:
		float* m_AttachedVar;
		std::string m_Title;
		float m_MinVal;
		float m_MaxVal;

	public:
		SliderFloat(std::string_view title, float* variable, float min, float max);

		void show() override;
	};
}
