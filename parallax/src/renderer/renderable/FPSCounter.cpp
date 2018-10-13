//#include <renderer/renderable/FPSCounter.h>
//
//#include <resources/Resources.h>
//
//namespace prx {
//
//	FPSCounter::FPSCounter(const Application& application)
//		: Label("0", hpm::vec3(10.0, 570.0, 0.0), Resources::getFont(RESOURCES_DEFAULT_FONT_ID), 0xffffffff),
//			m_Application(application) {}
//
//	FPSCounter::FPSCounter(hpm::vec3 position, unsigned int color, Font* font, const Application& application)
//		: Label("0", position, font, color), m_Application(application) {}
//
//	void FPSCounter::update() {
//		m_Text = std::to_string(m_Application.getFPS());
//	}
//}
