#pragma once
#include "ImGUIWidget.h"
#include <string>

namespace prx {
	class ToggleButton final : public ImGuiWidget {
	private:
		bool* m_AttachedVar;
		bool m_PrevButtonState;
		std::string m_Title;

	public:
		ToggleButton(std::string_view title, bool* variable);

		void show() override;
	};
}
