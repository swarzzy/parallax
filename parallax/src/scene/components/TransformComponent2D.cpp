#include <scene/components/TransformComponent2D.h>

namespace prx {
	TransformComponent2D::TransformComponent2D()
		: m_LocalMat(hpm::mat3::identity()),
		m_WorldMat(hpm::mat3::identity()),
		m_AnchorMat(hpm::mat3::identity()),
		m_Position(0.0f),
		m_Scale(1.0f),
		m_RotationAngle(0.0f),
		m_RotationRadius(0.0f),
		m_Size(0.0f),
		m_AnchorPoint(0.0f),
		m_LocalUpdate(true),
		m_WorldUpdate(true),
		m_AnchorUpdate(true)
	{}

	TransformComponent2D::~TransformComponent2D() {}

	void TransformComponent2D::init() {
		update();
	}

	void TransformComponent2D::update() {
		if (m_AnchorUpdate) {
			m_AnchorMat = hpm::mat3::translation(-(m_Size.x * m_AnchorPoint.x), -(m_Size.y * m_AnchorPoint.y));
			m_AnchorUpdate = false;
		}
		if (m_LocalUpdate) {
			m_LocalMat = hpm::mat3::translation(m_Position)
				* hpm::mat3::rotation(m_RotationAngle)
				* hpm::mat3::translation(m_RotationRadius, m_RotationRadius)
				* hpm::mat3::scale(hpm::vec2(m_Scale));
			m_LocalUpdate = false;
		}
		if (m_WorldUpdate) {
			m_WorldMat = m_WorldMat * m_LocalMat;
			m_WorldUpdate = false;
		}
	}
}

