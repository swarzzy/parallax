//#pragma once
//#include "../parallax/include/event/UI/OnClickListener.h"
//#include <iostream>
//#include "../parallax/include/renderer/renderable/UI/UIButtonBase.h"
//
//namespace prx::event {
//	class ButtonListener : public OnClickListener {
//	public:
//		Game* m_Game;
//
//		ButtonListener(Game* game) : m_Game(game) {};
//
//		void onClick(UIButtonBase* widget) override {
//			std::cout << "Button ID: "<< widget->getID() <<std::endl;
//			if (widget->getID() == 0)
//				m_Game->m_Sound->loop();
//			if (widget->getID() == 1)
//				m_Game->m_Sound->pause();
//		};
//	};
//}
