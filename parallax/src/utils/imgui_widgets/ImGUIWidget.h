#pragma once

namespace prx {
	class ImGUIWidget {
	public:
		ImGUIWidget() {};
		virtual ~ImGUIWidget() {};

		virtual void show() = 0;
	};
}