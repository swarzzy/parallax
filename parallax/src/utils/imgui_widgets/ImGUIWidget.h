#pragma once

namespace prx {
	class ImGuiWidget {
	public:
		ImGuiWidget() {};
		virtual ~ImGuiWidget() {};

		virtual void show() = 0;
	};
}