#pragma once

#include "ImGUIWidget.h"
#include <string>

namespace prx {
	class SliderInt final : public ImGuiWidget {
	private:
		int* m_AttachedVar;
		std::string m_Title;
		int m_MinVal;
		int m_MaxVal;

	public:
		SliderInt(std::string_view title, int* variable, int min, int max);

		void show() override;
	};
}

