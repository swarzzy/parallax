#include "SliderInt.h"

#include "../../ext/imgui/imgui.h"

namespace prx {
	SliderInt::SliderInt(std::string_view title, int* variable, int min, int max)
		: m_AttachedVar(variable)
		, m_Title(title)
		, m_MinVal(min)
		, m_MaxVal(max)
	{}

	void SliderInt::show() {
		ImGui::SliderInt(m_Title.c_str(), m_AttachedVar, m_MinVal, m_MaxVal);
	}
}
