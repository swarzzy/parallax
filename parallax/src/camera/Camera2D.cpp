#include <camera/Camera2D.h>

namespace prx {
	Camera2D::Camera2D() 
		: m_Position(hpm::vec2(0.0f)),
		  m_ProjectionMatrix(hpm::mat4::identity()),
		  m_ViewSpaceWidth(defaultViewSpaceWidth),
		  m_ViewSpaceHeight(defaultViewSpaceHeight),
		  m_NeedsUpdate(false)
	{}

	Camera2D::~Camera2D() {}
	
	void Camera2D::init(hpm::vec2 position, float near, float far, float viewSpaceWidth, float viewSpaceHeight) {
		m_Position = position;
		m_ViewSpaceWidth = viewSpaceWidth;
		m_ViewSpaceHeight = viewSpaceHeight;
		m_Near = near;
		m_Far = far;
		auto left = position.x - viewSpaceWidth / 2;
		auto top = position.y + viewSpaceHeight / 2;
		m_ProjectionMatrix = hpm::mat4::ortho(left, left + m_ViewSpaceWidth, top, top - m_ViewSpaceHeight, near, far);
	}

	void Camera2D::update() {
		if (m_NeedsUpdate) {
			auto left = m_Position.x - m_ViewSpaceWidth / 2;
			auto top = m_Position.y + m_ViewSpaceHeight / 2;
			m_ProjectionMatrix = hpm::mat4::ortho(left, left + m_ViewSpaceWidth, top, top - m_ViewSpaceHeight, m_Near, m_Far);
		}
	}
}
