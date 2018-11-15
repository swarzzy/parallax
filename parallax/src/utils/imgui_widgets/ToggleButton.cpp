#include "ToggleButton.h"

#include "../../ext/imgui/imgui.h"

namespace prx {
	ToggleButton::ToggleButton(std::string_view title, bool* variable)
		: m_AttachedVar(variable)
		, m_PrevButtonState(false)
		, m_Title(title)
	{}

	void ToggleButton::show() {
		bool state = ImGui::Button(m_Title.c_str());
		if (!m_PrevButtonState && state)
			*m_AttachedVar = !(*m_AttachedVar);
		m_PrevButtonState = state;
	}
}
