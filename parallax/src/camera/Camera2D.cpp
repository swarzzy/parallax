#include "../camera/Camera2D.h"
#include "../scene/Layer.h"
#include "../scene/Director.h"

namespace prx {
	Camera2D::Camera2D() 
		: m_Position(hpm::vec2(0.0f)),
		  m_ProjectionMatrix(hpm::mat4::identity()),
		  m_ViewSpaceSize(defaultViewSpaceWidth, defaultViewSpaceHeight),
		  m_NeedsUpdate(false)
	{}

	Camera2D::~Camera2D() {}
	
	void Camera2D::init(unsigned viewSpaceWidth, unsigned viewSpaceHeight) {
		m_ViewSpaceSize = hpm::vec2(static_cast<float>(viewSpaceWidth), static_cast<float>(viewSpaceHeight));
		m_ProjectionMatrix = hpm::mat4::ortho(m_Position.x, m_ViewSpaceSize.x + m_Position.x,
											  m_ViewSpaceSize.y + m_Position.y, m_Position.y,
											  static_cast<float>(Director::maxDepthValue()), 
											  static_cast<float>(Director::minDepthValue()));
	}

	void Camera2D::update() {
		if (m_NeedsUpdate) {
			m_ProjectionMatrix = hpm::mat4::ortho(m_Position.x, m_ViewSpaceSize.x + m_Position.x, 
												  m_ViewSpaceSize.y + m_Position.y, m_Position.y, 
												  static_cast<float>(Director::maxDepthValue()),
												  static_cast<float>(Director::minDepthValue()));
		}
	}
}
