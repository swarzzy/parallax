#pragma once
#ifndef _PARALLAX_EVENT_UI_ON_CLICK_LISTENER_H_
#define _PARALLAX_EVENT_UI_ON_CLICK_LISTENER_H_
#include "Listener.h"

namespace prx {
	class UIWidget;
}

namespace prx::event {
	class OnClickListener : public Listener {
	public:
		virtual void onClick(UIButton* widget) = 0;
		virtual void onRelease(UIButton* widget) {};
	};
}
#endif
