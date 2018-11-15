#include "SliderFloat.h"

#include "../../ext/imgui/imgui.h"

namespace prx {
	SliderFloat::SliderFloat(std::string_view title, float* variable, float min, float max)
		: m_AttachedVar(variable)
		, m_Title(title)
		, m_MinVal(min)
		, m_MaxVal(max)
	{}

	void SliderFloat::show() {
		ImGui::SliderFloat(m_Title.c_str(), m_AttachedVar, m_MinVal, m_MaxVal);
	}
}
